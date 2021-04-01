#include "Flow/Nodes/FlowNode_SimpleSpawn.h"
#include "FlowSubsystem.h"

UFlowNode_SimpleSpawn::UFlowNode_SimpleSpawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	InputNames = { TEXT("Spawn"), TEXT("Despawn") };
	OutputNames = { TEXT("Out"), TEXT("Spawned"), TEXT("Despawned") };
}

void UFlowNode_SimpleSpawn::PostLoad()
{
	Super::PostLoad();

	if (IdentityTag_DEPRECATED.IsValid())
	{
		IdentityTags = FGameplayTagContainer(IdentityTag_DEPRECATED);
		IdentityTag_DEPRECATED = FGameplayTag();
	}
}

void UFlowNode_SimpleSpawn::ExecuteInput(const FName& PinName)
{
	if (IdentityTags.IsValid())
	{
		if (PinName == TEXT("Spawn"))
		{
			int32 SpawnCount = 0;
			for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTags, EGameplayContainerMatchType::Any))
			{
				TArray<USpawnComponent*> NewSpawnComponents;
				FoundComponent->GetOwner()->GetComponents<USpawnComponent>(NewSpawnComponents);

				for (USpawnComponent* SpawnComponent : NewSpawnComponents)
				{
					if (!SpawnComponents.Contains(SpawnComponent))
					{
						if (SpawnComponent->Spawn(SpawnParams))
						{
							SpawnComponents.Emplace(SpawnComponent);
							SpawnCount++;
						}
					}
				}
			}

			if (SpawnCount > 0)
			{
				TriggerOutput(TEXT("Spawned"));
			}
		}
		else if (PinName == TEXT("Despawn"))
		{
			int32 DespawnCount = 0;
			for (TWeakObjectPtr<USpawnComponent> SpawnComponent : SpawnComponents)
			{
				if (SpawnComponent.IsValid())
				{
					SpawnComponent->Despawn();
					DespawnCount++;
				}
			}

			if (DespawnCount > 0)
			{
				TriggerOutput(TEXT("Despawned"), true);
			}
		}
	}
	else
	{
		LogError(MissingIdentityTag);
	}

	TriggerFirstOutput(true);
}

void UFlowNode_SimpleSpawn::Cleanup()
{
	SpawnComponents.Empty();
}

#if WITH_EDITOR 
FString UFlowNode_SimpleSpawn::GetNodeDescription() const
{
	const FString ClassString = SpawnParams.ActorClass ? SpawnParams.ActorClass->GetFName().ToString() : TEXT("Missing Actor Class!");
	return GetIdentityDescription(IdentityTags) + LINE_TERMINATOR + ClassString;
}
#endif

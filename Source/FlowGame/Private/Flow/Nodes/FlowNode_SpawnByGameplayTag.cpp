// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

#include "Flow/Nodes/FlowNode_SpawnByGameplayTag.h"
#include "FlowSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_SpawnByGameplayTag)

UFlowNode_SpawnByGameplayTag::UFlowNode_SpawnByGameplayTag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Actor");
#endif

	InputPins = {FFlowPin(TEXT("Spawn")), FFlowPin(TEXT("Despawn"))};
	OutputPins = {FFlowPin(TEXT("Spawned")), FFlowPin(TEXT("Despawned"))};
}

void UFlowNode_SpawnByGameplayTag::ExecuteInput(const FName& PinName)
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

void UFlowNode_SpawnByGameplayTag::Cleanup()
{
	SpawnComponents.Empty();
}

#if WITH_EDITOR
FString UFlowNode_SpawnByGameplayTag::GetNodeDescription() const
{
	const FString ClassString = SpawnParams.ActorClass ? SpawnParams.ActorClass->GetFName().ToString() : TEXT("Missing Actor Class!");
	return GetIdentityTagsDescription(IdentityTags) + LINE_TERMINATOR + ClassString;
}

EDataValidationResult UFlowNode_SpawnByGameplayTag::ValidateNode()
{
	if (IdentityTags.IsEmpty() || SpawnParams.ActorClass == nullptr)
	{
		if (IdentityTags.IsEmpty())
		{
			ValidationLog.Error<UFlowNode>(*UFlowNode::MissingIdentityTag, this);
		}
		if (SpawnParams.ActorClass == nullptr)
		{
			ValidationLog.Error<UFlowNode>(TEXT("Actor Class is missing or invalid"), this);
		}

		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif

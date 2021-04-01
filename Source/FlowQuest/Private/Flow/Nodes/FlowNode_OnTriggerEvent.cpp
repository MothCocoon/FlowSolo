#include "Flow/Nodes/FlowNode_OnTriggerEvent.h"
#include "Triggers/FlowTriggerComponent.h"

UFlowNode_OnTriggerEvent::UFlowNode_OnTriggerEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bReactOnOverlapping(false)
{
	// default behavior: react on Player overlapping with triggers
	if (FGameplayTag::IsValidGameplayTagString(TEXT("Player.Pawn")))
	{
		OverlappedActorTags = FGameplayTagContainer(FGameplayTag::RequestGameplayTag(TEXT("Player.Pawn")));
	}
}

void UFlowNode_OnTriggerEvent::PostLoad()
{
	Super::PostLoad();

	if (OverlappedActorTag_DEPRECATED.IsValid())
	{
		OverlappedActorTags = FGameplayTagContainer(OverlappedActorTag_DEPRECATED);
		OverlappedActorTag_DEPRECATED = FGameplayTag();
	}
}

void UFlowNode_OnTriggerEvent::ExecuteInput(const FName& PinName)
{
	if (OverlappedActorTags.IsValid())
	{
		Super::ExecuteInput(PinName);
	}
	else
	{
		LogError("Missing Overlapped Actor Tag");
	}
}

void UFlowNode_OnTriggerEvent::ObserveActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	if (!RegisteredActors.Contains(Actor))
	{
		if (UFlowTriggerComponent* FlowTriggerComponent = Cast<UFlowTriggerComponent>(Component))
		{
			RegisteredActors.Emplace(Actor, FlowTriggerComponent);

			TWeakObjectPtr<UFlowNode_OnTriggerEvent> SelfWeakPtr(this);
			FlowTriggerComponent->OnTriggerEvent.AddWeakLambda(this, [SelfWeakPtr](const bool bOverlapping, UFlowComponent* OtherFlowComponent)
			{
				if (SelfWeakPtr.IsValid() && SelfWeakPtr.Get()->bReactOnOverlapping == bOverlapping && OtherFlowComponent->IdentityTags.HasAnyExact(SelfWeakPtr.Get()->OverlappedActorTags))
				{
					SelfWeakPtr->TriggerOutput(TEXT("Success"), true);
				}
			});
		}
	}
}

void UFlowNode_OnTriggerEvent::ForgetActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	UFlowTriggerComponent* TriggerComponent = Cast<UFlowTriggerComponent>(Component);
	ensureAlways(TriggerComponent);

	TriggerComponent->OnTriggerEvent.RemoveAll(this);
}

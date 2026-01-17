// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

#include "Flow/Nodes/FlowNode_OnTriggerEvent.h"
#include "Flow/Triggers/FlowTriggerComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_OnTriggerEvent)

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
			FlowTriggerComponent->OnTriggerEvent.AddDynamic(this, &UFlowNode_OnTriggerEvent::OnTriggerEvent);
		}
	}
}

void UFlowNode_OnTriggerEvent::ForgetActor(TWeakObjectPtr<AActor> Actor, TWeakObjectPtr<UFlowComponent> Component)
{
	UFlowTriggerComponent* TriggerComponent = Cast<UFlowTriggerComponent>(Component);
	ensureAlways(TriggerComponent);

	TriggerComponent->OnTriggerEvent.RemoveAll(this);
}

void UFlowNode_OnTriggerEvent::OnTriggerEvent(const bool bOverlapping, UFlowComponent* OtherFlowComponent)
{
	if (bReactOnOverlapping == bOverlapping && OtherFlowComponent->IdentityTags.HasAnyExact(OverlappedActorTags))
	{
		OnEventReceived();
	}
}

#if WITH_EDITOR
EDataValidationResult UFlowNode_OnTriggerEvent::ValidateNode()
{
	if (IdentityTags.IsEmpty() || OverlappedActorTags.IsEmpty())
	{
		if (IdentityTags.IsEmpty())
		{
			ValidationLog.Error<UFlowNode>(*UFlowNode::MissingIdentityTag, this);
		}
		if (OverlappedActorTags.IsEmpty())
		{
			ValidationLog.Error<UFlowNode>(TEXT("Overlapped Actor Tag is missing!"), this);
		}
		
		return EDataValidationResult::Invalid;
	}

	return EDataValidationResult::Valid;
}
#endif

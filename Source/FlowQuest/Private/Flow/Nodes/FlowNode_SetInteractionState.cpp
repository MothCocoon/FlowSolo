#include "Flow/Nodes/FlowNode_SetInteractionState.h"
#include "Components/InteractionComponent.h"

#include "FlowSubsystem.h"

UFlowNode_SetInteractionState::UFlowNode_SetInteractionState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("World");
#endif

	InputNames = { TEXT("Enable"), TEXT("Disable") };
}

void UFlowNode_SetInteractionState::ExecuteInput(const FName& PinName)
{
	for (const TWeakObjectPtr<UFlowComponent>& FoundComponent : GetFlowSubsystem()->GetComponents<UFlowComponent>(IdentityTag))
	{
		TArray<UInteractionComponent*> FoundInteractions;
		FoundComponent->GetOwner()->GetComponents<UInteractionComponent>(FoundInteractions);
		if (FoundInteractions.Num() > 0)
		{
			if (PinName == TEXT("Enable"))
			{
				FoundInteractions[0]->Enable();
			}
			else
			{
				FoundInteractions[0]->Disable();
			}
		}
	}

	TriggerFirstOutput(true);
}

#if WITH_EDITOR 
FString UFlowNode_SetInteractionState::GetNodeDescription() const
{
	return IdentityTag.IsValid() ? IdentityTag.ToString() : MissingIdentityTag;
}
#endif

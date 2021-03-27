#pragma once

#include "GameplayTagContainer.h"

#include "Nodes/FlowNode.h"
#include "FlowNode_SetInteractionState.generated.h"

/**
 * Set Interaction State
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Set Interaction State"))
class FLOWQUEST_API UFlowNode_SetInteractionState : public UFlowNode
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "ObservedComponent")
	FGameplayTag IdentityTag;
	
protected:
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
#endif
};

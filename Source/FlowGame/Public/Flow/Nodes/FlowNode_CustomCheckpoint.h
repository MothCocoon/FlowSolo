// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "Nodes/FlowNode.h"
#include "FlowNode_CustomCheckpoint.generated.h"

/**
 *
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Checkpoint"))
class UFlowNode_CustomCheckpoint final : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void OnLoad_Implementation() override;
};

// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "Flow/Triggers/FlowTriggerBase.h"
#include "FlowTriggerCapsule.generated.h"

/** A capsule shaped trigger, used to generate overlap events in the level */
UCLASS()
class AFlowTriggerCapsule : public AFlowTriggerBase
{
	GENERATED_UCLASS_BODY()

#if WITH_EDITOR
	//~ Begin AActor Interface.
	virtual void EditorApplyScale(const FVector& DeltaScale, const FVector* PivotLocation, bool bAltDown, bool bShiftDown, bool bCtrlDown) override;
	//~ End AActor Interface.
#endif
};

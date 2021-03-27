#include "Flow/Nodes/FlowNode_OnTriggerEnter.h"

UFlowNode_OnTriggerEnter::UFlowNode_OnTriggerEnter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReactOnOverlapping = true;
}

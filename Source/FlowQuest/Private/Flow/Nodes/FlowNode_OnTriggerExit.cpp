#include "Flow/Nodes/FlowNode_OnTriggerExit.h"

UFlowNode_OnTriggerExit::UFlowNode_OnTriggerExit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReactOnOverlapping = false;
}

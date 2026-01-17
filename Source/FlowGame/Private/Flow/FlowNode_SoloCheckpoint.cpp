// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

#include "Flow/FlowNode_SoloCheckpoint.h"
#include "Flow/FlowSaveSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(FlowNode_SoloCheckpoint)

UFlowNode_SoloCheckpoint::UFlowNode_SoloCheckpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Graph");
#endif
}

void UFlowNode_SoloCheckpoint::ExecuteInput(const FName& PinName)
{
	if (GetWorld())
	{
		if (UFlowSaveSubsystem* SaveSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSaveSubsystem>())
		{
			SaveSubsystem->SaveGame();
		}
	}

	TriggerFirstOutput(true);
}

void UFlowNode_SoloCheckpoint::OnLoad_Implementation()
{
	TriggerFirstOutput(true);
}

#include "Core/FlowNode_SoloCheckpoint.h"
#include "FlowSubsystem.h"
#include "Core/SaveSubsystem.h"

UFlowNode_SoloCheckpoint::UFlowNode_SoloCheckpoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Utils");
#endif
}

void UFlowNode_SoloCheckpoint::ExecuteInput(const FName& PinName)
{
	if (GetWorld())
	{
		if (USaveSubsystem* SaveSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<USaveSubsystem>())
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

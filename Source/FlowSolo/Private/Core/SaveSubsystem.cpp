#include "Core/SaveSubsystem.h"

#include "FlowWorldSettings.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

FString USaveSubsystem::CheckpointSlotName = TEXT("Checkpoint");

USaveSubsystem::USaveSubsystem()
	: UFlowSubsystem()
{
}

bool USaveSubsystem::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	return HasAnyFlags(RF_ClassDefaultObject) ? false : ProcessConsoleExec(Cmd, Ar, nullptr);
}

void USaveSubsystem::SaveGame()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UFlowSaveGame::StaticClass());
	OnGameSaved(Cast<UFlowSaveGame>(NewSaveGame));

	UGameplayStatics::SaveGameToSlot(NewSaveGame, CheckpointSlotName, 0);
}

void USaveSubsystem::LoadGame()
{
	USaveGame* LoadedSave = UGameplayStatics::LoadGameFromSlot(CheckpointSlotName, 0);
	if (LoadedSave)
	{
		AbortActiveFlows();
		OnGameLoaded(Cast<UFlowSaveGame>(LoadedSave));

		const UFlowSubsystem* FlowSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFlowSubsystem>();
		const AFlowWorldSettings* WorldSettings = Cast<AFlowWorldSettings>(GetWorld()->GetWorldSettings());
		if (FlowSubsystem && WorldSettings && WorldSettings->GetFlowComponent()->LoadInstance())
		{
			WorldSettings->GetFlowComponent()->LoadRootFlow();
		}
	}
}

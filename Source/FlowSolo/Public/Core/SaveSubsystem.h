#pragma once

#include "FlowSubsystem.h"
#include "SaveSubsystem.generated.h"

/**
 * Minimal logic, just enough for testing purposes
 * WORK IN PROGRESS
 */
UCLASS()
class USaveSubsystem final : public UFlowSubsystem, public FSelfRegisteringExec
{
	GENERATED_BODY()

	USaveSubsystem();
	
public:
	static FString CheckpointSlotName;

	// FSelfRegisteringExec
	virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;

	void SaveGame();

	UFUNCTION(Exec, Category = "SaveSubsystem")
	void LoadGame();
};

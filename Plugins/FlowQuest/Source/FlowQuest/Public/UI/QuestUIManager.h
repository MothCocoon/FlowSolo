#pragma once

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "QuestUIManager.generated.h"

class UUserWidget;

/**
 *
 */
UCLASS()
class FLOWQUEST_API UQuestUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UQuestUIManager();
	
private:
	UPROPERTY()
	TMap<TSubclassOf<UUserWidget>, TObjectPtr<UUserWidget>> OpenedWidgets;

	UPROPERTY()
	TArray<TSubclassOf<UUserWidget>> HiddenWidgets;

public:
	void OpenWidget(const TSubclassOf<UUserWidget> WidgetClass);
	void CloseWidget(const TSubclassOf<UUserWidget> WidgetClass);
	void ToggleWidget(const TSubclassOf<UUserWidget> WidgetClass);

	void HideWidgets();
	void RestoreWidgets();
};

// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "SimpleUIManager.generated.h"

class UUserWidget;

/**
 *
 */
UCLASS()
class USimpleUIManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USimpleUIManager();
	
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

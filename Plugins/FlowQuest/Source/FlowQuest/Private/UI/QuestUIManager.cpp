#include "UI/QuestUIManager.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

UQuestUIManager::UQuestUIManager()
	: UGameInstanceSubsystem()
{
}

void UQuestUIManager::OpenWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (WidgetClass == nullptr || WidgetClass->HasAnyClassFlags(CLASS_Abstract) || OpenedWidgets.Contains(WidgetClass))
	{
		return;
	}

	UUserWidget* Widget = Cast<UUserWidget>(UWidgetBlueprintLibrary::Create(GetWorld(), *WidgetClass, GetWorld()->GetFirstPlayerController()));
	OpenedWidgets.Add(WidgetClass, Widget);
	Widget->AddToViewport();
}

void UQuestUIManager::CloseWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (UUserWidget* Widget = OpenedWidgets.FindRef(WidgetClass))
	{
		Widget->RemoveFromParent();
		OpenedWidgets.Remove(WidgetClass);
	}
}

void UQuestUIManager::ToggleWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (OpenedWidgets.Contains(WidgetClass))
	{
		CloseWidget(WidgetClass);
	}
	else
	{
		OpenWidget(WidgetClass);
	}
}

void UQuestUIManager::HideWidgets()
{
	for (auto WidgetIt = OpenedWidgets.CreateIterator(); WidgetIt; ++WidgetIt)
	{
		const TPair<TSubclassOf<UUserWidget>, UUserWidget*> Widget = *WidgetIt;

		HiddenWidgets.Add(Widget.Key);
		CloseWidget(Widget.Key);
	}
}

void UQuestUIManager::RestoreWidgets()
{
	for (const TSubclassOf<UUserWidget>& WidgetClass : HiddenWidgets)
	{
		OpenWidget(WidgetClass);
	}
	HiddenWidgets.Empty();
}

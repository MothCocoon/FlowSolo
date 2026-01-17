// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

#include "Gameplay/SimpleUIManager.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SimpleUIManager)

USimpleUIManager::USimpleUIManager()
{
}

void USimpleUIManager::OpenWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (WidgetClass == nullptr || WidgetClass->HasAnyClassFlags(CLASS_Abstract) || OpenedWidgets.Contains(WidgetClass))
	{
		return;
	}

	UUserWidget* Widget = Cast<UUserWidget>(UWidgetBlueprintLibrary::Create(GetWorld(), *WidgetClass, GetWorld()->GetFirstPlayerController()));
	OpenedWidgets.Add(WidgetClass, Widget);
	Widget->AddToViewport();
}

void USimpleUIManager::CloseWidget(const TSubclassOf<UUserWidget> WidgetClass)
{
	if (UUserWidget* Widget = OpenedWidgets.FindRef(WidgetClass))
	{
		Widget->RemoveFromParent();
		OpenedWidgets.Remove(WidgetClass);
	}
}

void USimpleUIManager::ToggleWidget(const TSubclassOf<UUserWidget> WidgetClass)
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

void USimpleUIManager::HideWidgets()
{
	for (auto WidgetIt = OpenedWidgets.CreateIterator(); WidgetIt; ++WidgetIt)
	{
		const TPair<TSubclassOf<UUserWidget>, UUserWidget*> Widget = *WidgetIt;

		HiddenWidgets.Add(Widget.Key);
		CloseWidget(Widget.Key);
	}
}

void USimpleUIManager::RestoreWidgets()
{
	for (const TSubclassOf<UUserWidget>& WidgetClass : HiddenWidgets)
	{
		OpenWidget(WidgetClass);
	}
	HiddenWidgets.Empty();
}

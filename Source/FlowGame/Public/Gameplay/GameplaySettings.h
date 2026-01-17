// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "Engine/DeveloperSettings.h"
#include "GameplaySettings.generated.h"

class UUserWidget;

/**
 *
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Gameplay"))
class  UGameplaySettings final : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Config, EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> InteractionWidget;
};

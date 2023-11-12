#pragma once

#include "Engine/DeveloperSettings.h"
#include "Templates/SubclassOf.h"
#include "QuestSettings.generated.h"

class UUserWidget;

/**
 *
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Quest"))
class FLOWQUEST_API UQuestSettings final : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

	static UQuestSettings* Get() { return CastChecked<UQuestSettings>(StaticClass()->GetDefaultObject()); }

	UPROPERTY(Config, EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> InteractionWidget;
};

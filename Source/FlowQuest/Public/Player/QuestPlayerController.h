#pragma once

#include "GameFramework/PlayerController.h"
#include "QuestPlayerController.generated.h"

class UInteractionComponent;

/**
 *
 */
UCLASS()
class FLOWQUEST_API AQuestPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

private:
	TArray<TWeakObjectPtr<UInteractionComponent>> PossibleInteractions;
	TWeakObjectPtr<UInteractionComponent> ActiveInteraction;
	
	void OnInteractionEnter(const TWeakObjectPtr<UInteractionComponent> Interaction);
	void OnInteractionExit(const TWeakObjectPtr<UInteractionComponent> Interaction);

	void ActivateInteraction(const TWeakObjectPtr<UInteractionComponent> Interaction);
	void DectivateInteraction();
	
	UFUNCTION()
	void OnInteractionUsed();
};

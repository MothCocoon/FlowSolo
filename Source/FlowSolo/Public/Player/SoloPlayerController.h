#pragma once

#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "SoloPlayerController.generated.h"

class UInteractionComponent;

/**
 *
 */
UCLASS()
class FLOWSOLO_API ASoloPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

public:	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* ExplorationContext;

	// Contains debug inputs, inactive in Shipping builds
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DebugContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* InteractionInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveForwardInput;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveRightInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CameraPitchInput;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CameraYawInput;

private:
	TWeakObjectPtr<class USoloInputComponent> SoloInputComponent;
	
public:
	virtual void SetupInputComponent() override;
	void SetExplorationContext() const;

	void MoveForward(const UInputAction* Action) const;
	void MoveRight(const UInputAction* Action) const;

	void AddPitch(const UInputAction* Action);
	void AddYaw(const UInputAction* Action);

	virtual void PlayerTick(float DeltaTime) override;

private:
	TArray<TWeakObjectPtr<UInteractionComponent>> PossibleInteractions;
	TWeakObjectPtr<UInteractionComponent> ActiveInteraction;
	
	void OnInteractionEnter(const TWeakObjectPtr<UInteractionComponent> Interaction);
	void OnInteractionExit(const TWeakObjectPtr<UInteractionComponent> Interaction);

	void ActivateInteraction(const TWeakObjectPtr<UInteractionComponent> Interaction);
	void DeactivateInteraction();
	
	void OnInteractionUsed() const;
};

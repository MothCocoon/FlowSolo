#include "Player/SoloPlayerController.h"

#include "Components/InteractionComponent.h"
#include "QuestSettings.h"
#include "UI/QuestUIManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASoloPlayerController::ASoloPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	UInteractionComponent::OnPlayerEnter.AddUObject(this, &ASoloPlayerController::OnInteractionEnter);
	UInteractionComponent::OnPlayerExit.AddUObject(this, &ASoloPlayerController::OnInteractionExit);
}

void ASoloPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetExplorationContext();

	SoloInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(SoloInputComponent.IsValid());

	// Exploration context
	{
		if (MoveForwardInput)
		{
			SoloInputComponent->BindActionValue(MoveForwardInput);
			SoloInputComponent->BindAction(MoveForwardInput, ETriggerEvent::Triggered, this, &ASoloPlayerController::MoveForward, MoveForwardInput);
		}

		if (MoveRightInput)
		{
			SoloInputComponent->BindActionValue(MoveRightInput);
			SoloInputComponent->BindAction(MoveRightInput, ETriggerEvent::Triggered, this, &ASoloPlayerController::MoveRight, MoveRightInput);
		}

		if (CameraPitchInput)
		{
			SoloInputComponent->BindActionValue(CameraPitchInput);
			SoloInputComponent->BindAction(CameraPitchInput, ETriggerEvent::Triggered, this, &ASoloPlayerController::AddPitch, CameraPitchInput);
		}

		if (CameraYawInput)
		{
			SoloInputComponent->BindActionValue(CameraYawInput);
			SoloInputComponent->BindAction(CameraYawInput, ETriggerEvent::Triggered, this, &ASoloPlayerController::AddYaw, CameraYawInput);
		}

		if (InteractionInput)
		{
			SoloInputComponent->BindAction(InteractionInput, ETriggerEvent::Started, this, &ASoloPlayerController::OnInteractionUsed);
		}
	}
}

void ASoloPlayerController::SetExplorationContext() const
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();

#if !UE_BUILD_SHIPPING
		Subsystem->AddMappingContext(DebugContext, 0);
#endif

		Subsystem->AddMappingContext(ExplorationContext, 1);
	}
}

void ASoloPlayerController::MoveForward(UInputAction* Action)
{
	if (!IsMoveInputIgnored() && GetPawn())
	{
		GetPawn()->AddMovementInput(GetControlRotation().Vector(), SoloInputComponent->GetBoundActionValue(Action).Get<float>());
	}
}

void ASoloPlayerController::MoveRight(UInputAction* Action)
{
	if (!IsMoveInputIgnored() && GetPawn())
	{
		GetPawn()->AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), SoloInputComponent->GetBoundActionValue(Action).Get<float>());
	}
}

void ASoloPlayerController::AddPitch(UInputAction* Action)
{
	if (!IsLookInputIgnored())
	{
		RotationInput.Pitch = SoloInputComponent->GetBoundActionValue(Action).Get<float>();
	}
}

void ASoloPlayerController::AddYaw(UInputAction* Action)
{
	if (!IsLookInputIgnored())
	{
		RotationInput.Yaw = SoloInputComponent->GetBoundActionValue(Action).Get<float>();
	}
}

void ASoloPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (PossibleInteractions.Num() > 0)
	{
		const FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
		PossibleInteractions.Sort([CameraLocation](const TWeakObjectPtr<UInteractionComponent>& A, const TWeakObjectPtr<UInteractionComponent>& B)
		{
			const float DistanceA = FVector::DistSquared(CameraLocation, A.Get()->GetComponentLocation());
			const float DistanceB = FVector::DistSquared(CameraLocation, B.Get()->GetComponentLocation());
			return DistanceA < DistanceB;
		});

		if (!ActiveInteraction.IsValid() && ActiveInteraction != PossibleInteractions[0])
		{
			ActivateInteraction(PossibleInteractions[0]);
		}
	}
	else if (ActiveInteraction.IsValid())
	{
		DeactivateInteraction();
	}
}

void ASoloPlayerController::OnInteractionEnter(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	PossibleInteractions.Add(Interaction);
}

void ASoloPlayerController::OnInteractionExit(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid() && ActiveInteraction == Interaction)
	{
		DeactivateInteraction();
	}

	PossibleInteractions.Remove(Interaction);
}

void ASoloPlayerController::ActivateInteraction(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid())
	{
		DeactivateInteraction();
	}

	ActiveInteraction = Interaction;
	GetGameInstance()->GetSubsystem<UQuestUIManager>()->OpenWidget(UQuestSettings::Get()->InteractionWidget);
}

void ASoloPlayerController::DeactivateInteraction()
{
	ActiveInteraction = nullptr;
	GetGameInstance()->GetSubsystem<UQuestUIManager>()->CloseWidget(UQuestSettings::Get()->InteractionWidget);
}

void ASoloPlayerController::OnInteractionUsed()
{
	if (ActiveInteraction.IsValid())
	{
		ActiveInteraction->OnUsed.Broadcast();
	}
}

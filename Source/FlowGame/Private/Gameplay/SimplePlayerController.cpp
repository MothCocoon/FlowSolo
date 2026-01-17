// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

#include "Gameplay/SimplePlayerController.h"

#include "Gameplay/GameplaySettings.h"
#include "Gameplay/InteractionComponent.h"
#include "Gameplay/SimpleUIManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SimplePlayerController)

ASimplePlayerController::ASimplePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	UInteractionComponent::OnPlayerEnter.AddUObject(this, &ASimplePlayerController::OnInteractionEnter);
	UInteractionComponent::OnPlayerExit.AddUObject(this, &ASimplePlayerController::OnInteractionExit);
}

void ASimplePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	SetExplorationContext();

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	check(EnhancedInputComponent.IsValid());

	// Exploration context
	{
		if (MoveForwardInput)
		{
			EnhancedInputComponent->BindActionValue(MoveForwardInput);
			EnhancedInputComponent->BindAction(MoveForwardInput.Get(), ETriggerEvent::Triggered, this, &ASimplePlayerController::MoveForward, MoveForwardInput.Get());
		}

		if (MoveRightInput)
		{
			EnhancedInputComponent->BindActionValue(MoveRightInput);
			EnhancedInputComponent->BindAction(MoveRightInput.Get(), ETriggerEvent::Triggered, this, &ASimplePlayerController::MoveRight, MoveRightInput.Get());
		}

		if (CameraPitchInput)
		{
			EnhancedInputComponent->BindActionValue(CameraPitchInput);
			EnhancedInputComponent->BindAction(CameraPitchInput.Get(), ETriggerEvent::Triggered, this, &ASimplePlayerController::AddPitch, CameraPitchInput.Get());
		}

		if (CameraYawInput)
		{
			EnhancedInputComponent->BindActionValue(CameraYawInput);
			EnhancedInputComponent->BindAction(CameraYawInput.Get(), ETriggerEvent::Triggered, this, &ASimplePlayerController::AddYaw, CameraYawInput.Get());
		}

		if (InteractionInput)
		{
			EnhancedInputComponent->BindAction(InteractionInput, ETriggerEvent::Started, this, &ASimplePlayerController::OnInteractionUsed);
		}
	}
}

void ASimplePlayerController::SetExplorationContext() const
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

void ASimplePlayerController::MoveForward(UInputAction* Action)
{
	if (!IsMoveInputIgnored() && GetPawn())
	{
		GetPawn()->AddMovementInput(GetControlRotation().Vector(), EnhancedInputComponent->GetBoundActionValue(Action).Get<float>());
	}
}

void ASimplePlayerController::MoveRight(UInputAction* Action)
{
	if (!IsMoveInputIgnored() && GetPawn())
	{
		GetPawn()->AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), EnhancedInputComponent->GetBoundActionValue(Action).Get<float>());
	}
}

void ASimplePlayerController::AddPitch(UInputAction* Action)
{
	if (!IsLookInputIgnored())
	{
		RotationInput.Pitch = EnhancedInputComponent->GetBoundActionValue(Action).Get<float>();
	}
}

void ASimplePlayerController::AddYaw(UInputAction* Action)
{
	if (!IsLookInputIgnored())
	{
		RotationInput.Yaw = EnhancedInputComponent->GetBoundActionValue(Action).Get<float>();
	}
}

void ASimplePlayerController::PlayerTick(float DeltaTime)
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

void ASimplePlayerController::OnInteractionEnter(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	PossibleInteractions.Add(Interaction);
}

void ASimplePlayerController::OnInteractionExit(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid() && ActiveInteraction == Interaction)
	{
		DeactivateInteraction();
	}

	PossibleInteractions.Remove(Interaction);
}

void ASimplePlayerController::ActivateInteraction(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid())
	{
		DeactivateInteraction();
	}

	ActiveInteraction = Interaction;
	GetGameInstance()->GetSubsystem<USimpleUIManager>()->OpenWidget(GetDefault<UGameplaySettings>()->InteractionWidget);
}

void ASimplePlayerController::DeactivateInteraction()
{
	ActiveInteraction = nullptr;
	GetGameInstance()->GetSubsystem<USimpleUIManager>()->CloseWidget(GetDefault<UGameplaySettings>()->InteractionWidget);
}

void ASimplePlayerController::OnInteractionUsed()
{
	if (ActiveInteraction.IsValid())
	{
		ActiveInteraction->OnUsed.Broadcast();
	}
}

#include "Player/QuestPlayerController.h"
#include "QuestSettings.h"

#include "Components/InteractionComponent.h"
#include "UI/QuestUIManager.h"

AQuestPlayerController::AQuestPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	UInteractionComponent::OnPlayerEnter.AddUObject(this, &AQuestPlayerController::OnInteractionEnter);
	UInteractionComponent::OnPlayerExit.AddUObject(this, &AQuestPlayerController::OnInteractionExit);
}

void AQuestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Interaction", IE_Released, this, &AQuestPlayerController::OnInteractionUsed);
}

void AQuestPlayerController::PlayerTick(float DeltaTime)
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
		DectivateInteraction();
	}
}

void AQuestPlayerController::OnInteractionEnter(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	PossibleInteractions.Add(Interaction);
}

void AQuestPlayerController::OnInteractionExit(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid() && ActiveInteraction == Interaction)
	{
		DectivateInteraction();
	}
	
	PossibleInteractions.Remove(Interaction);
}

void AQuestPlayerController::ActivateInteraction(const TWeakObjectPtr<UInteractionComponent> Interaction)
{
	if (ActiveInteraction.IsValid())
	{
		DectivateInteraction();
	}
	
	ActiveInteraction = Interaction;
	GetGameInstance()->GetSubsystem<UQuestUIManager>()->OpenWidget(UQuestSettings::Get()->InteractionWidget);
}	

void AQuestPlayerController::DectivateInteraction()
{
	ActiveInteraction = nullptr;
	GetGameInstance()->GetSubsystem<UQuestUIManager>()->CloseWidget(UQuestSettings::Get()->InteractionWidget);
}

void AQuestPlayerController::OnInteractionUsed()
{
	if (ActiveInteraction.IsValid())
	{
		ActiveInteraction->OnUsed.Broadcast();
	}
}

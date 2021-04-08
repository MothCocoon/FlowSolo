#include "Triggers/FlowTriggerVolume.h"
#include "Triggers/FlowTriggerComponent.h"

#include "Components/BrushComponent.h"

AFlowTriggerVolume::AFlowTriggerVolume(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static FName CollisionProfileName(TEXT("Trigger"));
	GetBrushComponent()->SetCollisionProfileName(CollisionProfileName);

	bColored = true;
	BrushColor.R = 100;
	BrushColor.G = 255;
	BrushColor.B = 100;
	BrushColor.A = 255;

	bReplicates = true;
	FlowTriggerComponent = CreateDefaultSubobject<UFlowTriggerComponent>(TEXT("FlowTriggerComponent"));
}

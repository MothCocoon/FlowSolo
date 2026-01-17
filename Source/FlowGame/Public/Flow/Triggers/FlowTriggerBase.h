// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "GameFramework/Actor.h"
#include "FlowTriggerBase.generated.h"

class UFlowTriggerComponent;

class UBillboardComponent;
class UShapeComponent;

/** An actor used to generate collision events (begin/end overlap) in the level. */
UCLASS(ClassGroup=Flow, Abstract, ConversionRoot, MinimalAPI)
class AFlowTriggerBase : public AActor
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(Category = FlowTriggerBase, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFlowTriggerComponent> FlowTriggerComponent;
	
	UPROPERTY(Category = FlowTriggerBase, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UShapeComponent> CollisionComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UBillboardComponent> SpriteComponent;
#endif

public:
	UShapeComponent* GetCollisionComponent() const { return CollisionComponent; }

#if WITH_EDITORONLY_DATA
	UBillboardComponent* GetSpriteComponent() const { return SpriteComponent; }
#endif
};

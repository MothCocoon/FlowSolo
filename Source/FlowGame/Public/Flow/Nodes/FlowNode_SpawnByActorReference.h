// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "Nodes/FlowNode.h"

#include "Gameplay/SpawnComponent.h"
#include "FlowNode_SpawnByActorReference.generated.h"

/**
 * Spawn by Actor Reference
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Spawn by Actor Reference"))
class UFlowNode_SpawnByActorReference : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "SpawnPoint")
	TArray<TSoftObjectPtr<AActor>> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (ShowOnlyInnerProperties))
	FQuestSpawnParams SpawnParams;

	TSet<TWeakObjectPtr<USpawnComponent>> SpawnComponents;
	
protected:
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;
	
#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
	virtual EDataValidationResult ValidateNode() override;
#endif
};

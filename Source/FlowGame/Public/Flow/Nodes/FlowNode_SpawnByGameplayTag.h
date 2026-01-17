// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
#pragma once

#include "GameplayTagContainer.h"

#include "Nodes/FlowNode.h"

#include "Gameplay/SpawnComponent.h"
#include "FlowNode_SpawnByGameplayTag.generated.h"

/**
 * Spawn by Gameplay Tag
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Spawn by Gameplay Tag"))
class UFlowNode_SpawnByGameplayTag : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "SpawnPoint")
	FGameplayTagContainer IdentityTags;

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

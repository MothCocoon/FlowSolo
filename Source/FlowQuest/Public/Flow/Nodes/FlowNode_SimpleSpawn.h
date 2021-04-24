#pragma once

#include "GameplayTagContainer.h"

#include "Nodes/FlowNode.h"

#include "Components/SpawnComponent.h"
#include "FlowNode_SimpleSpawn.generated.h"

/**
 * Simple Spawn
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Simple Spawn"))
class FLOWQUEST_API UFlowNode_SimpleSpawn : public UFlowNode
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Spawn Point")
	FGameplayTagContainer IdentityTags;

	UPROPERTY(EditAnywhere, Category = "Spawn", meta = (ShowOnlyInnerProperties))
	FQuestSpawnParams SpawnParams;

	TSet<TWeakObjectPtr<USpawnComponent>> SpawnComponents;
	
protected:
	virtual void PostLoad() override;
	
	virtual void ExecuteInput(const FName& PinName) override;
	virtual void Cleanup() override;
	
#if WITH_EDITOR
public:
	virtual FString GetNodeDescription() const override;
#endif

private:
	UPROPERTY()
	FGameplayTag IdentityTag_DEPRECATED;
};

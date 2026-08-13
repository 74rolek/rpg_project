#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionInteractableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class USelectionInteractable : public UInterface
{
	GENERATED_BODY()
};

class ISelectionInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetSelected(bool bIsSelected);
};

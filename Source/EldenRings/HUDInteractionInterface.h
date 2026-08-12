#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInteractionInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UHUDInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUD")
	void ShowUpgradeWidget(AActor* SourceActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUD")
	void HideUpgradeWidget(AActor* SourceActor);
};

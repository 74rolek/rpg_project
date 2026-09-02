#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "Interactable.h"
#include "SelectionInteractableInterface.h"
#include "Ognisko_Base.generated.h"

UCLASS()
class ELDENRINGS_API AOgnisko_Base : public AActor, public IInteractable, public ISelectionInteractable
{
	GENERATED_BODY()

public:
	AOgnisko_Base();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ognisko")
	FString RowTable;

	UFUNCTION(BlueprintPure, Category = "Ognisko")
	FString PobierzRowTable() const { return RowTable; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ognisko")
	UStaticMeshComponent* ModelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ognisko")
	UBoxComponent* StrefaInterakcji;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ognisko")
	TSubclassOf<UUserWidget> UlepszeniePostaciWidgetClass;

	UPROPERTY()
	UUserWidget* UlepszeniePostaciWidgetInstance;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ognisko")
	bool bCzyGraczWStrefie = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ognisko")
	bool bMenuOtworzone = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bJestWybrany = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	void TryUseCampfire(AParent_Gracza* Player);

	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	void OpenUpgradeWidget();

	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	void CloseUpgradeWidget();

	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	bool CzyMoznaOtworzycMenu() const { return bCzyGraczWStrefie; }

	virtual void Interact_Implementation(AActor* Interactor) override;
	virtual void SetSelected_Implementation(bool bIsSelected) override;
};
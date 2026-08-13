#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HUDInteractionInterface.h"
#include "SelectionInteractableInterface.h"
#include "Parent_Gracza.generated.h"

class AOgnisko_Base;

UCLASS()
class ELDENRINGS_API AParent_Gracza : public ACharacter
{
	GENERATED_BODY()

public:
	AParent_Gracza();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool CzyJestPrzyOgnisku() const;

	AOgnisko_Base* GetBestNearbyCampfire() const;
	bool IsCampfireInFrontOfCamera(const AActor* Campfire) const;
	void UpdateSelectedCampfire();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OpenUpgradePanel();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void CloseUpgradePanel();

	void SetNearbyCampfire(AOgnisko_Base* Campfire);
	void ClearNearbyCampfire(AOgnisko_Base* Campfire);

protected:
	virtual void BeginPlay() override;

	// Funkcja Tick dodana do obsługi ciągłego zabierania staminy podczas sprintu
	virtual void Tick(float DeltaTime) override;

	// Obiekty sterowania w Unreal Engine
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractAction;

	// Akcja skoku dodana do systemu sterowania
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	// Funkcje poruszania się
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void InteractPressed();

	// Funkcje sprintu
	void StartSprint();
	void StopSprint();

	// Funkcja obsługująca skok ze sprawdzaniem staminy
	void ZrobSkok();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

	// Prędkości poruszania się
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1200.0f;

	// Akumulatory dla płynnego odejmowania i regeneracji staminy
	float SprintStaminaAccumulator = 0.0f;
	float RegenStaminaAccumulator = 0.0f;

private:
	TArray<TWeakObjectPtr<AOgnisko_Base>> NearbyCampfires;
	TWeakObjectPtr<AOgnisko_Base> SelectedCampfire;
};

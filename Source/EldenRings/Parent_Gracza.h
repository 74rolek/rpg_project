#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Parent_Gracza.generated.h"

UCLASS()
class ELDENRINGS_API AParent_Gracza : public ACharacter
{
	GENERATED_BODY()

public:
	AParent_Gracza();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Obiekty sterowania w Unreal Engine
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* SprintAction;

	// Funkcje poruszania się
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

	// Funkcje sprintu
	void StartSprint();
	void StopSprint();

	// Prędkości poruszania się
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 1200.0f;
};
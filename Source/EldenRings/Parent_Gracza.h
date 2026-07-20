#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RPGPlayer.generated.h" // Upewnij się, że ta nazwa pasuje do Twojego pliku!

UCLASS()
class TWÓJPROJEKT_API ARPGPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Konstruktor klasy
	ARPGPlayer();

	// Wywoływane, aby powiązać funkcjonalność z klawiszami
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Wywoływane na starcie gry
	virtual void BeginPlay() override;

	// Plik konfiguracyjny sterowania (Input Mapping Context)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	// Akcja odpowiedzialna za ruch (W, A, S, D)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	// Akcja odpowiedzialna za rozglądanie się (Myszka)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	// Funkcje obsługujące ruch i myszkę
	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
};

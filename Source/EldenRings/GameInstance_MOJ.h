#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MojGameInstance.generated.h"

UCLASS()
class TWOJANAZWAPROJEKTU_API UMojGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Build_postaci

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Sila;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Witalnosc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zrecznosc;


	//Statystyki

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int32 AktualnyXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalna_Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalne_HP;

	// Funkcja do dodawania XP dostępna z poziomu Blueprintów
	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	void DodajXP(int32 Ilosc);
};
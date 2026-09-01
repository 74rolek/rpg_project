// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Pojedynczy_save_1_postac.generated.h"



UCLASS()
class ELDENRINGS_API UPojedynczy_save_1_postac : public USaveGame
{
	GENERATED_BODY()

public:

	
	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	int Zapisz_level;

	UPROPERTY(BlueprintReadWrite, Category = "SaveData")
	FString Zapisz_Ostatnie_ognisko;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_statystyke_Sila;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_statystyke_Witalnosc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_statystyke_Zrecznosc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_statystyke_Poise_Build;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_statystyke_Inteligencja;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zapisz_XP_twojej_postaci;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int XP_Zaginione;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	FVector Pozycja_XP_Zaginionego;













};

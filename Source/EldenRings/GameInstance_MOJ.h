#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstance_MOJ.generated.h"

UCLASS()
class ELDENRINGS_API UGameInstance_MOJ : public UGameInstance
{
	GENERATED_BODY()

public:

	// --- BUILD POSTACI ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Sila = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Witalnosc = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zrecznosc = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Mana = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Poise_Build = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Inteligencja = 10;


	// --- STATYSTYKI ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int AktualnyXP = 0;

	// Zdrowie
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int HP = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalne_HP = 100;

	// Mana
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Statystyka_Mana = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalna_Mana = 50;

	// Wytrzymałość
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Wytzymalosc = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalna_Wytzymalosc = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Regeneracja_Wytrzymalosci = 30;

	// Poise (Równowaga)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Poise = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalne_Poise = 30;


	// --- OBRAŻENIA ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Fizyczne = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Magiczne = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Obrazajace = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Ogniste = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Zmarzniecie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Krwawienie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Zatrucie = 0;


	// --- ODPORNOŚCI ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Fizyczna = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Magiczna = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Obrazajaca = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Ognista = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Zmarzniecie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Krwawienie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	int Odpornosc_Zatrucie = 0;


	// --- FUNKCJE ---

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	void DodajXP(int Ilosc);

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	void Wyzeruj_XP();

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	int Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	void PodniesLevel(int Ilosc);

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeSila();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeWitalnosc();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeZrecznosc();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeMana();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeInteligencja();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykePoise();
};
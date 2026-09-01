#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pojedynczy_save_1_postac.h"
#include "GameInstance_MOJ.generated.h"

UCLASS()
class ELDENRINGS_API UGameInstance_MOJ : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	bool GodMode = false;

	// --- BUILD POSTACI ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Sila = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Witalnosc = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Zrecznosc = 0;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Poise_Build = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Inteligencja = 0;


	// --- STATYSTYKI ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int AktualnyXP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Build_postaci")
	int Mana = 10;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	float HP = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalne_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	float SzybkoscAtaku = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	float NormalnaSzybkoscAtaku = 15.f;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalna_Mana = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Wytrzymalosc = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalna_Wytrzymalosc = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Regeneracja_Wytrzymalosci = 30;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Poise = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Maksymalne_Poise = 30;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki")
	int Szansa_na_Obrazenia_Krytyczne = 30;



	// --- OBRAŻENIA ---

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Fizyczne = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obrażenia")
	int Obrazenia_Magiczne;

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
float Odpornosc_Fizyczna = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Magiczna = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Obrazajaca = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Ognista = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Zmarzniecie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Krwawienie = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	float Odpornosc_Zatrucie = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Odporności")
	APlayerController* PC;


	// --- FUNKCJE ---

	UFUNCTION(BlueprintCallable, Category = "Walka")
	void TakeDamageAdvanced(
		float Fizyczne,
		float Magiczne,
		float Obrazajace,
		float Ogniste,
		float Zmarzniecie,
		float Krwawienie,
		float Zatrucie,
		bool &czy_nie_zyje
	);

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	int DajAtakPostaci();

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
	int WyliczWartoscStatystyki(float Baza, int PoziomStatystyki, float ParametrA, float ParametrB);

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykeInteligencja();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	bool UlepszStatystykePoise();

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	void Zabierz_stamine(int Ilosc_stamina, bool& Czy_zabralo_stamine);

	UFUNCTION(BlueprintCallable, Category = "Build_postaci")
	void Regeneruj_Stamine(int Ilosc_stamina);

	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	void Odpocznij_Przy_Ognisku();


	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	void Incjanizacja_wszystkiego();

	UFUNCTION(BlueprintCallable, Category = "Statystyki")
	int Wyliczanie_ulepszen_procentowych(float A, float Poziom_Statystyki, float B, float Baza, float C);

	UFUNCTION(BlueprintCallable, Category = "Gracz")
	void Respawn();

	UFUNCTION(BlueprintCallable, Category = "Gracz")
	void Pojaw_gracza();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveGame();




};

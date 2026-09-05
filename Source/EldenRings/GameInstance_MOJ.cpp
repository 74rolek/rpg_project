#include "GameInstance_MOJ.h"
#include "Kismet/GameplayStatics.h"
#include "Ognisko_Base.h"
#include "EngineUtils.h"

// I N C J A L I Z A C J A
void UGameInstance_MOJ::Incjanizacja_wszystkiego()
{
	PC = GetWorld()->GetFirstPlayerController();
	WczytajGre(TEXT("Save 1"));
	PrzeliczStatystyki(true);
	TeleportujDoOstatniegoOgniska();
}

void UGameInstance_MOJ::TakeDamageAdvanced(
	float Fizyczne,
	float Magiczne,
	float Obrazajace,
	float Ogniste,
	float Zmarzniecie,
	float Krwawienie,
	float Zatrucie,
	bool& czy_nie_zyje)


{
	float RedukcjaFizyczna = FMath::Clamp(1.0f - (Odpornosc_Fizyczna / 100.0f), 0.0f, 1.0f);
	float RedukcjaMagiczna = FMath::Clamp(1.0f - (Odpornosc_Magiczna / 100.0f), 0.0f, 1.0f);
	float RedukcjaObrazajaca = FMath::Clamp(1.0f - (Odpornosc_Obrazajaca / 100.0f), 0.0f, 1.0f);
	float RedukcjaOgnista = FMath::Clamp(1.0f - (Odpornosc_Ognista / 100.0f), 0.0f, 1.0f);
	float RedukcjaZmarzniecie = FMath::Clamp(1.0f - (Odpornosc_Zmarzniecie / 100.0f), 0.0f, 1.0f);
	float RedukcjaKrwawienie = FMath::Clamp(1.0f - (Odpornosc_Krwawienie / 100.0f), 0.0f, 1.0f);
	float RedukcjaZatrucie = FMath::Clamp(1.0f - (Odpornosc_Zatrucie / 100.0f), 0.0f, 1.0f);

	float OstateczneObrazenia =
		(Fizyczne * RedukcjaFizyczna) +
		(Magiczne * RedukcjaMagiczna) +
		(Obrazajace * RedukcjaObrazajaca) +
		(Ogniste * RedukcjaOgnista) +
		(Zmarzniecie * RedukcjaZmarzniecie) +
		(Krwawienie * RedukcjaKrwawienie) +
		(Zatrucie * RedukcjaZatrucie);

	if (!GodMode)
	{
		HP -= OstateczneObrazenia;
	}

	

	UE_LOG(LogTemp, Warning, TEXT("Otrzymano obrażenia: %f | Pozostałe HP: %f"), OstateczneObrazenia, HP);

	if (HP <= 0.0f)
	{
		HP = 0.0f;
		czy_nie_zyje = true;

		UE_LOG(LogTemp, Error, TEXT("You died"));

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You died"));
		}
	}
}

int UGameInstance_MOJ::DajAtakPostaci()
{
	int FinalneObrazenia = Obrazenia_Fizyczne + (Zrecznosc * 3) + (Sila * 1);
	return FinalneObrazenia;
}

void UGameInstance_MOJ::DodajXP(int Ilosc)
{
	AktualnyXP += Ilosc;


	UE_LOG(LogTemp, Warning, TEXT("==== DODANO XP: %d | AKTUALNY XP W GAMEINSTANCE: %d ===="), Ilosc, AktualnyXP);
}

void UGameInstance_MOJ::Zgub_XP()
{
	As_Pojednynczy_save_1_postac->XP_Zaginione = AktualnyXP;
	As_Pojednynczy_save_1_postac->Pozycja_XP_Zaginionego = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();



	AktualnyXP = 0;	
}

int UGameInstance_MOJ::Daj_mi_wymagane_XP_do_ulepszenia_postaci()
{
	float BazowyKoszt = 100.0f;
	float Koszt = BazowyKoszt + FMath::Pow(static_cast<float>(Level), 1.7f) * 35.0f;

	return FMath::RoundToInt(Koszt);
}

void UGameInstance_MOJ::PodniesLevel(int Ilosc)
{
	Level += Ilosc;
}








/// I  ///////////////////////////////////////////////////////////////
/// V
///ulepszenie statystyk


bool UGameInstance_MOJ::UlepszStatystykeSila()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Sila++;
		Obrazenia_Fizyczne = WyliczWartoscStatystyki(20, Sila, 4.7f, 0.1f);
		Odpornosc_Fizyczna = Wyliczanie_ulepszen_procentowych(5,Sila, 3 , 14, 8.833f);

		
		Maksymalna_Wytrzymalosc = WyliczWartoscStatystyki(39,Sila,5,0.7f );
		Wytrzymalosc = Maksymalna_Wytrzymalosc;

		SaveGame(TEXT("Save 1"));

		return true;
	}
	return false;
}

bool UGameInstance_MOJ::UlepszStatystykeWitalnosc()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Witalnosc++;
		Maksymalne_HP = WyliczWartoscStatystyki(230, Witalnosc, 5.1f,0.9f);
		HP = Maksymalne_HP;
		
		SaveGame(TEXT("Save 1"));

		return true;
	}

	return false;
}

bool UGameInstance_MOJ::UlepszStatystykeZrecznosc()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Zrecznosc++;

		SzybkoscAtaku = WyliczWartoscStatystyki(15,Zrecznosc,1,0.1f);

		SaveGame(TEXT("Save 1"));

		return true;
	}
	return false;
}

bool UGameInstance_MOJ::UlepszStatystykeInteligencja()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Inteligencja++;
		Maksymalna_Mana = WyliczWartoscStatystyki(50, Inteligencja, 4, 0.9f);
		Obrazenia_Magiczne = WyliczWartoscStatystyki(20, Inteligencja, 10, 0.2f);
		
		SaveGame(TEXT("Save 1"));

		return true;
	}
	return false;
}





bool UGameInstance_MOJ::UlepszStatystykePoise()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Poise_Build++;
		Maksymalne_Poise = WyliczWartoscStatystyki(50, Poise_Build, 4, 0.09f);
		Szansa_na_Obrazenia_Krytyczne = Wyliczanie_ulepszen_procentowych(3,Poise_Build,2,20,20);
		Poise = Maksymalne_Poise;
		
		SaveGame(TEXT("Save 1"));

		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////








void UGameInstance_MOJ::Zabierz_stamine(int Ilosc_stamina, bool& Czy_zabralo_stamine)
{
	if (Wytrzymalosc > 0)
	{
		Wytrzymalosc = FMath::Clamp(Wytrzymalosc - Ilosc_stamina, 0, Maksymalna_Wytrzymalosc);
		Czy_zabralo_stamine = true;
	}
	else
	{
		Czy_zabralo_stamine = false;
	}
}

void UGameInstance_MOJ::Regeneruj_Stamine(int Ilosc_stamina)
{
	if (Wytrzymalosc < Maksymalna_Wytrzymalosc)
	{
		Wytrzymalosc = FMath::Clamp(Wytrzymalosc + Ilosc_stamina, 0, Maksymalna_Wytrzymalosc);
	}
}

void UGameInstance_MOJ::Odpocznij_Przy_Ognisku(FString RowOgniska)
{
	if (!As_Pojednynczy_save_1_postac)
	{
		As_Pojednynczy_save_1_postac = Cast<UPojedynczy_save_1_postac>(UGameplayStatics::CreateSaveGameObject(UPojedynczy_save_1_postac::StaticClass()));
	}
	PrzeliczStatystyki(true);
	if (As_Pojednynczy_save_1_postac)
	{
		As_Pojednynczy_save_1_postac->Zapisz_Ostatnie_ognisko = RowOgniska;
	}
	
	SaveGame(TEXT("Save 1"));
	UGameplayStatics::OpenLevel(this, FName(TEXT("Scena_Glowna")));
}

int UGameInstance_MOJ::Wyliczanie_ulepszen_procentowych(float A, float Poziom_Statystyki, float B, float Baza, float C)
{

	 return FMath::RoundToInt( FMath::Loge(((A + Poziom_Statystyki) / A) + 1.0) / FMath::Loge(B) * Baza - C);



}

void UGameInstance_MOJ::Respawn()
{
	PrzeliczStatystyki(true);
	SaveGame(TEXT("Save 1"));
	UGameplayStatics::OpenLevel(this, FName(TEXT("Scena_Glowna")));
}

void UGameInstance_MOJ::Pojaw_gracza()
{
	
	if (PC)
	{

		PC->bShowMouseCursor = false;


		FInputModeGameOnly InputMode;


		InputMode.SetConsumeCaptureMouseDown(false);

		PC->SetInputMode(InputMode);
	}

}

void UGameInstance_MOJ::Shutdown()
{
	Super::Shutdown();

}

void UGameInstance_MOJ::PrzeliczStatystyki(bool bPelneZasoby)
{
	Maksymalne_HP = WyliczWartoscStatystyki(230, Witalnosc, 5.1f, 0.9f);
	Obrazenia_Fizyczne = WyliczWartoscStatystyki(20, Sila, 4.7f, 0.1f);
	Maksymalna_Wytrzymalosc = WyliczWartoscStatystyki(39, Sila, 5.0f, 0.7f);
	SzybkoscAtaku = WyliczWartoscStatystyki(15, Zrecznosc, 1.0f, 0.1f);
	NormalnaSzybkoscAtaku = SzybkoscAtaku;
	Maksymalna_Mana = WyliczWartoscStatystyki(50, Inteligencja, 4.0f, 0.9f);
	Obrazenia_Magiczne = WyliczWartoscStatystyki(20, Inteligencja, 10.0f, 0.2f);
	Maksymalne_Poise = WyliczWartoscStatystyki(50, Poise_Build, 4.0f, 0.09f);
	Odpornosc_Fizyczna = Wyliczanie_ulepszen_procentowych(5, Sila, 3, 14, 8.833f);
	Szansa_na_Obrazenia_Krytyczne = Wyliczanie_ulepszen_procentowych(3, Poise_Build, 2, 20, 20);
	if (bPelneZasoby)
	{
		HP = Maksymalne_HP;
		Mana = Maksymalna_Mana;
		Wytrzymalosc = Maksymalna_Wytrzymalosc;
		Poise = Maksymalne_Poise;
	}
}

void UGameInstance_MOJ::WczytajGre(const FString& NazwaSave)
{
	UPojedynczy_save_1_postac* LoadedCharacter = Cast<UPojedynczy_save_1_postac>(UGameplayStatics::LoadGameFromSlot(NazwaSave, 0));
	if (!LoadedCharacter)
	{
		As_Pojednynczy_save_1_postac = Cast<UPojedynczy_save_1_postac>(UGameplayStatics::CreateSaveGameObject(UPojedynczy_save_1_postac::StaticClass()));
		return;
	}
	As_Pojednynczy_save_1_postac = LoadedCharacter;
	Level = LoadedCharacter->Zapisz_level;
	Sila = LoadedCharacter->Zapisz_statystyke_Sila;
	Witalnosc = LoadedCharacter->Zapisz_statystyke_Witalnosc;
	Zrecznosc = LoadedCharacter->Zapisz_statystyke_Zrecznosc;
	Poise_Build = LoadedCharacter->Zapisz_statystyke_Poise_Build;
	Inteligencja = LoadedCharacter->Zapisz_statystyke_Inteligencja;
	AktualnyXP = LoadedCharacter->Zapisz_XP_twojej_postaci;
}

void UGameInstance_MOJ::TeleportujDoOstatniegoOgniska()
{
	if (!GetWorld() || !As_Pojednynczy_save_1_postac || As_Pojednynczy_save_1_postac->Zapisz_Ostatnie_ognisko.IsEmpty()) return;
	for (TActorIterator<AOgnisko_Base> It(GetWorld()); It; ++It)
	{
		if (It->PobierzRowTable() == As_Pojednynczy_save_1_postac->Zapisz_Ostatnie_ognisko)
		{
			if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)) PlayerPawn->SetActorLocation(It->GetActorLocation());
			return;
		}
	}
}

void UGameInstance_MOJ::ZapiszPokonanegoSpecjalnegoMoba(const FString& Identyfikator)
{
	if (As_Pojednynczy_save_1_postac && !As_Pojednynczy_save_1_postac->PokonaneSpecjalneMoby.Contains(Identyfikator))
	{
		As_Pojednynczy_save_1_postac->PokonaneSpecjalneMoby.Add(Identyfikator);
		SaveGame(TEXT("Save 1"));
	}
}

bool UGameInstance_MOJ::CzySpecjalnyMobJestPokonany(const FString& Identyfikator) const
{
	return As_Pojednynczy_save_1_postac && As_Pojednynczy_save_1_postac->PokonaneSpecjalneMoby.Contains(Identyfikator);
}

void UGameInstance_MOJ::ZapiszPokonanegoBossa(const FString& Identyfikator)
{
	if (As_Pojednynczy_save_1_postac && !As_Pojednynczy_save_1_postac->PokonaniBossowie.Contains(Identyfikator))
	{
		As_Pojednynczy_save_1_postac->PokonaniBossowie.Add(Identyfikator);
		SaveGame(TEXT("Save 1"));
	}
}

bool UGameInstance_MOJ::CzyBossJestPokonany(const FString& Identyfikator) const
{
	return As_Pojednynczy_save_1_postac && As_Pojednynczy_save_1_postac->PokonaniBossowie.Contains(Identyfikator);
}

void UGameInstance_MOJ::ZapiszOtwartaSkrzynke(const FString& Identyfikator)
{
	if (As_Pojednynczy_save_1_postac && !As_Pojednynczy_save_1_postac->OtwarteSkrzynki.Contains(Identyfikator))
	{
		As_Pojednynczy_save_1_postac->OtwarteSkrzynki.Add(Identyfikator);
		SaveGame(TEXT("Save 1"));
	}
}

bool UGameInstance_MOJ::CzySkrzynkaJestOtwarta(const FString& Identyfikator) const
{
	return As_Pojednynczy_save_1_postac && As_Pojednynczy_save_1_postac->OtwarteSkrzynki.Contains(Identyfikator);
}

void UGameInstance_MOJ::ZapiszOdkryteOgnisko(const FString& Identyfikator)
{
	if (As_Pojednynczy_save_1_postac && !As_Pojednynczy_save_1_postac->OdkryteOgniska.Contains(Identyfikator))
	{
		As_Pojednynczy_save_1_postac->OdkryteOgniska.Add(Identyfikator);
		SaveGame(TEXT("Save 1"));
	}
}

bool UGameInstance_MOJ::CzyOgniskoJestOdkryte(const FString& Identyfikator) const
{
	return As_Pojednynczy_save_1_postac && As_Pojednynczy_save_1_postac->OdkryteOgniska.Contains(Identyfikator);
}

void UGameInstance_MOJ::Na_wylanczaniu_gry()
{

	SaveGame(TEXT("Save 1"));

}


//---- SAVE GAME -----\\

void UGameInstance_MOJ::SaveGame(FString Nazwa_save)
{
	
	


	if (As_Pojednynczy_save_1_postac)
	{
	
		As_Pojednynczy_save_1_postac->Zapisz_level = Level;
        
		As_Pojednynczy_save_1_postac->Zapisz_statystyke_Sila = Sila;
		As_Pojednynczy_save_1_postac->Zapisz_statystyke_Witalnosc = Witalnosc;
		As_Pojednynczy_save_1_postac->Zapisz_statystyke_Zrecznosc = Zrecznosc;
		As_Pojednynczy_save_1_postac->Zapisz_statystyke_Poise_Build = Poise_Build;
		As_Pojednynczy_save_1_postac->Zapisz_statystyke_Inteligencja = Inteligencja;

		As_Pojednynczy_save_1_postac->Zapisz_XP_twojej_postaci = AktualnyXP;

		FString SlotName = Nazwa_save;
		int32 UserIndex = 0;

		if (UGameplayStatics::SaveGameToSlot(As_Pojednynczy_save_1_postac, SlotName, UserIndex))
		{
			UE_LOG(LogTemp, Log, TEXT("Gra została pomyślnie zapisana w slocie: %s"), *SlotName);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Błąd! Nie udało się zapisać gry."));
		}
	}
}

void UGameInstance_MOJ::Przeladuj_swiat()
{
	Respawn();
}






int UGameInstance_MOJ::WyliczWartoscStatystyki(float Baza, int PoziomStatystyki, float ParametrA, float ParametrB)
{
	
	return FMath::RoundToInt(Baza + (PoziomStatystyki * ParametrA) + (FMath::Pow(static_cast<float>(PoziomStatystyki), 2.0f) * ParametrB));
}








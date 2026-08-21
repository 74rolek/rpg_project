#include "GameInstance_MOJ.h"

void UGameInstance_MOJ::TakeDamageAdvanced(
	float Fizyczne,
	float Magiczne,
	float Obrazajace,
	float Ogniste,
	float Zmarzniecie,
	float Krwawienie,
	float Zatrucie)
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

void UGameInstance_MOJ::Wyzeruj_XP()
{
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
		Odpornosc_Fizyczna = 1;

		
		Maksymalna_Wytrzymalosc = WyliczWartoscStatystyki(39,Sila,5,0.7f );
		Wytrzymalosc = Maksymalna_Wytrzymalosc;

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
		Szansa_na_Obrazenia_Krytyczne = FMath::Loge(((3.0f + Poise_Build) / 3.0f) + 1.0f) / FMath::Loge(2.0f) * 20.0f - 20;
		Poise = Maksymalne_Poise;
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

void UGameInstance_MOJ::Odpocznij_Przy_Ognisku()
{
	HP = Maksymalne_HP;
	Wytrzymalosc = Maksymalna_Wytrzymalosc;
	Mana = Maksymalna_Mana;
}

void UGameInstance_MOJ::Incjanizacja_wszystkiego()
{

		
		Maksymalne_HP = WyliczWartoscStatystyki(230.0f, Witalnosc, 5.1f, 0.9f);
		HP = Maksymalne_HP;

		
		Obrazenia_Fizyczne = WyliczWartoscStatystyki(20.0f, Sila, 4.7f, 0.1f);
		Maksymalna_Wytrzymalosc = WyliczWartoscStatystyki(39.0f, Sila, 5.0f, 0.7f);
		Wytrzymalosc = Maksymalna_Wytrzymalosc;

		
		SzybkoscAtaku = WyliczWartoscStatystyki(15.0f, Zrecznosc, 1.0f, 0.1f);
		NormalnaSzybkoscAtaku = SzybkoscAtaku;

		Maksymalna_Mana = WyliczWartoscStatystyki(50.0f, Inteligencja, 4.0f, 0.9f);
		Mana = Maksymalna_Mana;
		Obrazenia_Magiczne = WyliczWartoscStatystyki(20.0f, Inteligencja, 10.0f, 0.2f);

		
		Maksymalne_Poise = WyliczWartoscStatystyki(50.0f, Poise_Build, 4.0f, 0.09f);
		Poise = Maksymalne_Poise;

		UE_LOG(LogTemp, Log, TEXT("Zainicjalizowano statystyki postaci na poziomie %d."), Level);
	



}



int UGameInstance_MOJ::WyliczWartoscStatystyki(float Baza, int PoziomStatystyki, float ParametrA, float ParametrB)
{
	
	return FMath::RoundToInt(Baza + (PoziomStatystyki * ParametrA) + (FMath::Pow(static_cast<float>(PoziomStatystyki), 2.0f) * ParametrB));
}



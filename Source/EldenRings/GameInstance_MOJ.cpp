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

	HP -= OstateczneObrazenia;

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

	// Wypisze informację w konsoli Output Log w Unrealu
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

bool UGameInstance_MOJ::UlepszStatystykeSila()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Sila++;
		Obrazenia_Fizyczne += 2;

		// Dodaje wytrzymałość przy ulepszaniu siły
		Maksymalna_Wytrzymalosc += 10;
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
		Maksymalne_HP += 25;
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
		Obrazenia_Fizyczne += 1;
		return true;
	}
	return false;
}

bool UGameInstance_MOJ::UlepszStatystykeMana()
{
	int WymaganyXP = Daj_mi_wymagane_XP_do_ulepszenia_postaci();

	if (AktualnyXP >= WymaganyXP)
	{
		AktualnyXP -= WymaganyXP;
		PodniesLevel(1);
		Mana++;
		Maksymalna_Mana += 15;
		Statystyka_Mana = Maksymalna_Mana;
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
		Obrazenia_Magiczne += 3;
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
		Maksymalne_Poise += 5;
		Poise = Maksymalne_Poise;
		return true;
	}
	return false;
}

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
	Statystyka_Mana = Maksymalna_Mana;
}

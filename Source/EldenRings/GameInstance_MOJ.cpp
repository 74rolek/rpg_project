#include "GameInstance_MOJ.h"

void UGameInstance_MOJ::DodajXP(int Ilosc)
{
	AktualnyXP += Ilosc;
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
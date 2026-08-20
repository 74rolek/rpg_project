#include "BlueprintFunctionLibrary_moj.h"
#include "Math/UnrealMathUtility.h"

float UBlueprintFunctionLibrary_moj::WyliczFinalneObrazenia(
	float Fizyczne,
	float Magiczne,
	float Obrazajace,
	float Ogniste,
	float Zmarzniecie,
	float Krwawienie,
	float Zatrucie,
	float Odpornosc_Fizyczna,
	float Odpornosc_Magiczna,
	float Odpornosc_Obrazajaca,
	float Odpornosc_Ognista,
	float Odpornosc_Zmarzniecie,
	float Odpornosc_Krwawienie,
	float Odpornosc_Zatrucie,
	int Inteligencja)
{
	float LimitRedukcji = 0.9999f;
	float MnoznikSkalowania = 0.005f;

	auto ObliczRedukcje = [LimitRedukcji, MnoznikSkalowania](float Odpornosc) -> float
		{
			float Redukcja = LimitRedukcji * (1.0f - FMath::Exp(-Odpornosc * MnoznikSkalowania));
			return FMath::Clamp(Redukcja, 0.0f, LimitRedukcji);
		};


	float BonusInteligencji = static_cast<float>(Inteligencja) * 2.0f;

	float EfektywnaOdpornoscMagiczna = Odpornosc_Magiczna + BonusInteligencji;
	float EfektywnaOdpornoscObrazajaca = Odpornosc_Obrazajaca + BonusInteligencji;

	
	float RedukcjaFizyczna = ObliczRedukcje(Odpornosc_Fizyczna);
	float RedukcjaMagiczna = ObliczRedukcje(EfektywnaOdpornoscMagiczna);
	float RedukcjaObrazajaca = ObliczRedukcje(EfektywnaOdpornoscObrazajaca);
	float RedukcjaOgnista = ObliczRedukcje(Odpornosc_Ognista);
	float RedukcjaZmarzniecie = ObliczRedukcje(Odpornosc_Zmarzniecie);
	float RedukcjaKrwawienie = ObliczRedukcje(Odpornosc_Krwawienie);
	float RedukcjaZatrucie = ObliczRedukcje(Odpornosc_Zatrucie);


	float KoncoweFizyczne = Fizyczne * (1.0f - RedukcjaFizyczna);
	float KoncoweMagiczne = Magiczne * (1.0f - RedukcjaMagiczna);
	float KoncoweObrazajace = Obrazajace * (1.0f - RedukcjaObrazajaca);
	float KoncoweOgniste = Ogniste * (1.0f - RedukcjaOgnista);
	float KoncoweZmarzniecie = Zmarzniecie * (1.0f - RedukcjaZmarzniecie);
	float KoncoweKrwawienie = Krwawienie * (1.0f - RedukcjaKrwawienie);
	float KoncoweZatrucie = Zatrucie * (1.0f - RedukcjaZatrucie);

	float SumaObrazen = KoncoweFizyczne + KoncoweMagiczne + KoncoweObrazajace +
		KoncoweOgniste + KoncoweZmarzniecie + KoncoweKrwawienie + KoncoweZatrucie;

	return FMath::Max(0.0f, SumaObrazen);
}
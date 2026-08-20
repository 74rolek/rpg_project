#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintFunctionLibrary_moj.generated.h"

UCLASS()
class ELDENRINGS_API UBlueprintFunctionLibrary_moj : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Walka | Obrazenia")
	static float WyliczFinalneObrazenia(
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
		int Inteligencja
	);
	
};
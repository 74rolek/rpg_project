#include "MojGameInstance.h"

void UMojGameInstance::DodajXP(int32 Ilosc)
{
	AktualnyXP += Ilosc;

	UE_LOG(LogTemp, Warning, TEXT("Dodano %d XP! Aktualny stan: %d"), Ilosc, AktualnyXP);
}
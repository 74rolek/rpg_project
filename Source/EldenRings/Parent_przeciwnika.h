#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Parent_przeciwnika.generated.h"

UCLASS()
class ELDENRINGS_API AParent_przeciwnika : public ACharacter
{
	GENERATED_BODY()

public:

	AParent_przeciwnika();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float HP_przeciwnika;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float XP_ktore_daje_po_zabicu_go;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Mnoznik_szybkosci_ataku = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_fizyczne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_magiczne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_obrazajace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_ogniste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_zmarzniecie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_krwawnienie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Obrazenia_zatrucie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_fizyczne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_magiczne;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_obrazajace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_ogniste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_zmarzniecie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_krwawienie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Statystyki przeciwnika", meta = (ExposeOnSpawn = "true"))
	float Odpornosci_zatrucie;



};

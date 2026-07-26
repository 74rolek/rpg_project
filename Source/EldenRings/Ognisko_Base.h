#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Ognisko_Base.generated.h"

UCLASS()
class ELDENRINGS_API AOgnisko_Base : public AActor
{
	GENERATED_BODY()

public:
	AOgnisko_Base();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ognisko")
	UStaticMeshComponent* ModelMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ognisko")
	UBoxComponent* StrefaInterakcji;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Ognisko")
	bool bCzyGraczWStrefie = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Ognisko")
	bool CzyMoznaOtworzycMenu() const { return bCzyGraczWStrefie; }
};
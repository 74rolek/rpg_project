// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Parent_przeciwnika.generated.h"

UCLASS()
class ELDENRINGS_API AParent_przeciwnika : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AParent_przeciwnika();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Parent_przeciwnika.h"

// Sets default values
AParent_przeciwnika::AParent_przeciwnika()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AParent_przeciwnika::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParent_przeciwnika::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParent_przeciwnika::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


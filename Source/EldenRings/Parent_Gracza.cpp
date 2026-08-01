#include "Parent_Gracza.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance_MOJ.h"

AParent_Gracza::AParent_Gracza()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AParent_Gracza::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AParent_Gracza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(GetGameInstance()))
	{
		bool bIsSprinting = GetCharacterMovement() && GetCharacterMovement()->MaxWalkSpeed == SprintSpeed && GetVelocity().Size2D() > 0.0f;

		if (bIsSprinting)
		{
			bool bUdaloSieZabrac = false;
			int KosztSprintu = FMath::RoundToInt(25.0f * DeltaTime);

			GI->Zabierz_stamine(KosztSprintu, bUdaloSieZabrac);

			if (!bUdaloSieZabrac || GI->Wytrzymalosc <= 0)
			{
				StopSprint();
			}
		}
		else
		{
			if (GI->Wytrzymalosc < GI->Maksymalna_Wytrzymalosc)
			{
				int SzybkoscRegeneracji = GI->Regeneracja_Wytrzymalosci > 0 ? GI->Regeneracja_Wytrzymalosci : 10;
				int IloscRegeneracji = FMath::RoundToInt(static_cast<float>(SzybkoscRegeneracji) * DeltaTime);

				if (IloscRegeneracji == 0)
				{
					IloscRegeneracji = 1;
				}

				GI->Regeneruj_Stamine(IloscRegeneracji);
			}
		}
	}
}

void AParent_Gracza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AParent_Gracza::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AParent_Gracza::Look);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AParent_Gracza::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AParent_Gracza::StopSprint);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AParent_Gracza::ZrobSkok);
	}
}

void AParent_Gracza::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AParent_Gracza::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AParent_Gracza::StartSprint()
{
	if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(GetGameInstance()))
	{
		if (GI->Wytrzymalosc > 0)
		{
			if (GetCharacterMovement())
			{
				GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
			}
		}
	}
}

void AParent_Gracza::StopSprint()
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AParent_Gracza::ZrobSkok()
{
	if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(GetGameInstance()))
	{
		bool bUdaloSieZabrac = false;
		int KosztSkoku = 15;

		GI->Zabierz_stamine(KosztSkoku, bUdaloSieZabrac);

		if (bUdaloSieZabrac)
		{
			Jump();
		}
	}
}

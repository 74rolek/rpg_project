#include "Parent_Gracza.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameInstance_MOJ.h" // Załączenie nagłówka Twojego GameInstance

AParent_Gracza::AParent_Gracza()
{
	// Włączenie funkcji Tick dla tej postaci
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

	// Ustawienie domyślnej prędkości na chodzenie
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}

void AParent_Gracza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// --- OBSŁUGA KONSUMPCJI STAMINY PODCZAS SPRINTU ---
	// Sprawdzamy czy postać aktualnie biegnie oraz czy faktycznie porusza się po ziemi (Velocity > 0)
	if (GetCharacterMovement() && GetCharacterMovement()->MaxWalkSpeed == SprintSpeed && GetVelocity().Size2D() > 0.0f)
	{
		if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(GetGameInstance()))
		{
			bool bUdaloSieZabrac = false;

			// Koszt sprintu na sekundę (np. 25 punktów staminy pomnożone przez DeltaTime)
			int KosztSprintu = FMath::RoundToInt(25.0f * DeltaTime);

			GI->Zabierz_stamine(KosztSprintu, bUdaloSieZabrac);

			// Jeśli skończyła się stamina lub nie udało się jej pobrać, zatrzymaj sprint
			if (!bUdaloSieZabrac || GI->Wytrzymalosc <= 0)
			{
				StopSprint();
			}
		}
	}
}

void AParent_Gracza::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Podpięcie ruchu i myszki
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AParent_Gracza::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AParent_Gracza::Look);

		// Podpięcie sprintu (naciśnięcie i puszczenie Shift)
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AParent_Gracza::StartSprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AParent_Gracza::StopSprint);

		// Podpięcie nowej akcji skoku ze staminą
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
		// Nie pozwól zacząć sprintu, jeśli gracz nie ma staminy
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
		int KosztSkoku = 15; // Stały koszt staminy za jeden skok

		GI->Zabierz_stamine(KosztSkoku, bUdaloSieZabrac);

		// Skaczemy tylko wtedy, kiedy funkcja w GameInstance potwierdziła zabranie staminy
		if (bUdaloSieZabrac)
		{
			Jump();
		}
	}
}

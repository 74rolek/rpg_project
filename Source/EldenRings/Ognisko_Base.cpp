#include "Ognisko_Base.h"
#include "Parent_Gracza.h"
#include "GameInstance_MOJ.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AOgnisko_Base::Interact_Implementation(AActor* Interactor)
{
	AParent_Gracza* Player = Cast<AParent_Gracza>(Interactor);
	if (!Player)
	{
		return;
	}

	Player->OpenUpgradePanel();
}

void AOgnisko_Base::SetSelected_Implementation(bool bIsSelected)
{
	bJestWybrany = bIsSelected;

	if (!bIsSelected && bMenuOtworzone)
	{
		CloseUpgradeWidget();
	}
}

AOgnisko_Base::AOgnisko_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	ModelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ModelMesh"));
	RootComponent = ModelMesh;

	StrefaInterakcji = CreateDefaultSubobject<UBoxComponent>(TEXT("StrefaInterakcji"));
	StrefaInterakcji->SetupAttachment(RootComponent);
}

void AOgnisko_Base::BeginPlay()
{
	Super::BeginPlay();

	StrefaInterakcji->OnComponentBeginOverlap.AddDynamic(this, &AOgnisko_Base::OnOverlapBegin);
	StrefaInterakcji->OnComponentEndOverlap.AddDynamic(this, &AOgnisko_Base::OnOverlapEnd);
}

void AOgnisko_Base::TryUseCampfire(AParent_Gracza* Player)
{
	if (!Player || !bCzyGraczWStrefie)
	{
		return;
	}

	OpenUpgradeWidget();
}

void AOgnisko_Base::OpenUpgradeWidget()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}

	if (UlepszeniePostaciWidgetClass && !UlepszeniePostaciWidgetInstance)
	{
		UlepszeniePostaciWidgetInstance = CreateWidget<UUserWidget>(PC, UlepszeniePostaciWidgetClass);
	}

	if (UlepszeniePostaciWidgetInstance && !UlepszeniePostaciWidgetInstance->IsInViewport())
	{
		UlepszeniePostaciWidgetInstance->AddToViewport();
	}

	if (UlepszeniePostaciWidgetInstance)
	{
		bMenuOtworzone = true;
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}
}

void AOgnisko_Base::CloseUpgradeWidget()
{
	if (UlepszeniePostaciWidgetInstance && UlepszeniePostaciWidgetInstance->IsInViewport())
	{
		UlepszeniePostaciWidgetInstance->RemoveFromParent();
	}

	bMenuOtworzone = false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}
}

void AOgnisko_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	AParent_Gracza* Gracza = Cast<AParent_Gracza>(OtherActor);
	if (!Gracza)
	{
		return;
	}

	bCzyGraczWStrefie = true;
	if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(Gracza->GetGameInstance()))
	{
		GI->UstawGraczaPrzyOgnisku(true);
	}
	Gracza->SetNearbyCampfire(this);
}

void AOgnisko_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	AParent_Gracza* Gracza = Cast<AParent_Gracza>(OtherActor);
	if (!Gracza)
	{
		return;
	}

	bCzyGraczWStrefie = false;
	if (UGameInstance_MOJ* GI = Cast<UGameInstance_MOJ>(Gracza->GetGameInstance()))
	{
		GI->UstawGraczaPrzyOgnisku(false);
	}
	Gracza->ClearNearbyCampfire(this);

	if (bMenuOtworzone)
	{
		CloseUpgradeWidget();
	}
}
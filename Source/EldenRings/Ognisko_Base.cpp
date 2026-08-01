#include "Ognisko_Base.h"
#include "Parent_Gracza.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

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

void AOgnisko_Base::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AParent_Gracza* Gracza = Cast<AParent_Gracza>(OtherActor);
		if (Gracza)
		{
			bCzyGraczWStrefie = true;

			if (UlepszeniePostaciWidgetClass && !UlepszeniePostaciWidgetInstance)
			{
				APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
				if (PC)
				{
					UlepszeniePostaciWidgetInstance = CreateWidget<UUserWidget>(PC, UlepszeniePostaciWidgetClass);
					if (UlepszeniePostaciWidgetInstance)
					{
						UlepszeniePostaciWidgetInstance->AddToViewport();
						PC->SetInputMode(FInputModeGameAndUI());
						PC->bShowMouseCursor = true;
					}
				}
			}
			else if (UlepszeniePostaciWidgetInstance && !UlepszeniePostaciWidgetInstance->IsInViewport())
			{
				UlepszeniePostaciWidgetInstance->AddToViewport();
				APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
				if (PC)
				{
					PC->SetInputMode(FInputModeGameAndUI());
					PC->bShowMouseCursor = true;
				}
			}
		}
	}
}

void AOgnisko_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		AParent_Gracza* Gracza = Cast<AParent_Gracza>(OtherActor);
		if (Gracza)
		{
			bCzyGraczWStrefie = false;

			if (UlepszeniePostaciWidgetInstance && UlepszeniePostaciWidgetInstance->IsInViewport())
			{
				UlepszeniePostaciWidgetInstance->RemoveFromParent();
				APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
				if (PC)
				{
					PC->SetInputMode(FInputModeGameOnly());
					PC->bShowMouseCursor = false;
				}
			}
		}
	}
}
#include "Ognisko_Base.h"

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
		bCzyGraczWStrefie = true;
	}
}

void AOgnisko_Base::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		bCzyGraczWStrefie = false;
	}
}
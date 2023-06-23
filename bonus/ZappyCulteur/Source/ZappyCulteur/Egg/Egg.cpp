#include "Egg.h"
#include "Components/StaticMeshComponent.h"

AEgg::AEgg()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEgg::BeginPlay()
{
	Super::BeginPlay();
}

void AEgg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEgg::SetId(FString id)
{
	m_id = id;
}

void AEgg::KillEgg()
{
	Destroy();
}

FString AEgg::GetEggId() const
{
	return m_id;
}

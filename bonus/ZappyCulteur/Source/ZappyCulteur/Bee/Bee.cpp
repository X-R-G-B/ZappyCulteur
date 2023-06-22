#include "Bee.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABee::ABee()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABee::BeginPlay()
{
	Super::BeginPlay();
}

void ABee::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float positionOffset = FMath::RandRange(0, 40);

	if (m_isMoving)
	{
		FVector direction = m_toGoPosition - GetActorLocation();
		direction.Normalize();
		SetActorLocation(GetActorLocation() + direction * m_beeSpeed * DeltaTime);
		if (FVector::Dist(GetActorLocation(), m_toGoPosition) < positionOffset)
		{
			m_isMoving = false;
		}
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(), FVector(m_toGoPosition.X, m_toGoPosition.Y, m_toGoPosition.Z)
		);
		FRotator newRotation = FRotator(0, rotation.Yaw, 0);
		SetActorRotation(newRotation);
	}

	if (m_isIncantating && m_IncantationEmitter)
	{
		m_IncantationEmitter->SetWorldLocation(GetActorLocation());
	}
}

void ABee::StartIncantation()
{
	m_isIncantating = true;
	FRotator rotator = FRotator::ZeroRotator;
	FVector location = FVector::ZeroVector;

	UParticleSystem* ParticleSystem = incantationParticule.LoadSynchronous();
	UParticleSystemComponent* ParticleSystemComponent = nullptr;

	if (ParticleSystem)
	{
		rotator.Pitch = 90;
		location = GetActorLocation();
		ParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, location, rotator, true);
	}
	m_IncantationEmitter = ParticleSystemComponent;
}

void ABee::StopIncantation()
{
	m_isIncantating = false;

	if (m_IncantationEmitter)
	{
		m_IncantationEmitter->DestroyComponent();
		m_IncantationEmitter = nullptr;
	}
}

void ABee::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FString ABee::GetBeeId() const
{
	return m_beeId;
}

FString ABee::GetBeeTeam() const
{
	return m_beeTeam;
}

int32 ABee::GetBeeLevel() const
{
	return m_beeLevel;
}

void ABee::SetBeeId(FString id)
{
	m_beeId = id;
}

void ABee::SetBeeTeam(FString team)
{
	m_beeTeam = team;
}

void ABee::SetBeeLevel(int32 level)
{
	m_beeLevel = level;
}

void ABee::InitBee(FString id, FString team, int32 level, int32 orientation, int32 x, int32 y)
{
	m_beeId = id;
	m_beeTeam = team;
	m_beeLevel = level;
	m_beeOrientation = orientation;
	m_beeHeight = FMath::RandRange(m_beeHeightMin, m_beeHeightMax);
	SetActorLocation(FVector(x, y, m_beeHeight));
}

void ABee::GoToPosition(int32 x, int32 y, int32 orientation)
{
	m_isMoving = true;
	m_beeOrientation = orientation;
	m_toGoPosition = FVector(x, y, m_beeHeight);
}

FVector2D ABee::GetBeeTileNumber() const
{
	FVector2D tileNumber;

	tileNumber.X = GetActorLocation().X / m_grassBlockSize;
	tileNumber.Y = GetActorLocation().Y / m_grassBlockSize;
	return tileNumber;
}

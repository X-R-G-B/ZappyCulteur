#include "BeeUpdater.h"
#include "Bee.h"
#include "Kismet/GameplayStatics.h"

void UBeeUpdater::startBeesIncantation(int32 x, int32 y, int32 level, FString playerId)
{
    UE_LOG(LogTemp, Warning, TEXT("UBeeUpdater::startBeesIncantation"));
    UWorld* world = GetWorld();
    TArray<AActor*> actors;

    UGameplayStatics::GetAllActorsOfClass(world, ABee::StaticClass(), actors);
    for (AActor* actor : actors)
    {
        ABee* bee = Cast<ABee>(actor);
        if (bee->GetBeeId() == playerId)
        {
            bee->StartIncantation();
            AddIncantationData(x, y, level, playerId);
        }
    }
}

void UBeeUpdater::AddIncantationData(int32 x, int32 y, int32 level, FString playerId)
{
    FIncantation incantation;
    incantation.x = x;
    incantation.y = y;
    incantation.level = level;
    incantation.playerId = playerId;
    m_incantations.Add(incantation);
}

void UBeeUpdater::RemoveIncantationData(int32 x, int32 y, FString playerId)
{
    for (int32 i = 0; i < m_incantations.Num(); ++i)
    {
        if (m_incantations[i].x == x && m_incantations[i].y == y && m_incantations[i].playerId == playerId)
        {
            m_incantations.RemoveAt(i);
            return;
        }
    }
}

bool UBeeUpdater::IsIncantationDataExist(int32 x, int32 y, FString playerId)
{
    for (int32 i = 0; i < m_incantations.Num(); ++i)
    {
        if (m_incantations[i].x == x && m_incantations[i].y == y && m_incantations[i].playerId == playerId)
        {
            return true;
        }
    }
    return false;
}

void UBeeUpdater::stopBeesIncantation(int32 x, int32 y, FString result)
{
    UE_LOG(LogTemp, Warning, TEXT("UBeeUpdater::stopBeesIncantation"));
    UWorld* world = GetWorld();
    TArray<AActor*> actors;

    UGameplayStatics::GetAllActorsOfClass(world, ABee::StaticClass(), actors);
    for (AActor* actor : actors)
    {
        ABee* bee = Cast<ABee>(actor);
        if (IsIncantationDataExist(x, y, bee->GetBeeId()))
        {
            bee->StopIncantation();
            RemoveIncantationData(x, y, bee->GetBeeId());
        }
    }
}

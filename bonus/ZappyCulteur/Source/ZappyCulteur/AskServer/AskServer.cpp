#include "AskServer.h"
#include "Kismet/GameplayStatics.h"
#include "../Bee/Bee.h"
#include "../Network/NetworkManager.h"

void UAskServer::update(float deltaTime)
{
    m_timeSinceLastAsk += deltaTime;
    if (m_timeSinceLastAsk > 1)
    {
        m_timeSinceLastAsk = 0;
        askForBees();
        askForRessources();
    }
}

void UAskServer::askForBees()
{
    UWorld* World = GetWorld();
    FString message = "ppo ";
    FString messageToSend;

    if (World)
    {
        TArray<AActor*> FoundActors;

        UGameplayStatics::GetAllActorsOfClass(World, ABee::StaticClass(), FoundActors);
        for (auto& Actor : FoundActors)
        {
            ABee* Bee = Cast<ABee>(Actor);
            if (Bee != nullptr)
            {
                messageToSend = "ppo " + Bee->GetBeeId();
                askServerDelegate.Broadcast(messageToSend);
            }
        }
    }
}

void UAskServer::askForRessources()
{
    askServerDelegate.Broadcast("mct");
}

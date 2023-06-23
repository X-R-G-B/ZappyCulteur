#include "CommandHandler.h"
#include "Kismet/GameplayStatics.h"
#include "../Bee/Bee.h"
#include "../Egg/Egg.h"

/*static const TMap<FString, ECommandType> CommandMap = {
    { "ebo", ECommandType::PLAYER_CONNECTION_FOR_AN_EGG },
};*/

UCommandHandler::UCommandHandler() :
    m_commandMap({
        { "msz", [this](const TArray<FString>& parameters) { this->launchMapCreation(parameters); } },
        { "pnw", [this](const TArray<FString>& parameters) { this->launchPlayerConnection(parameters); } },
        { "ppo", [this](const TArray<FString>& parameters) { this->launchPlayerPosition(parameters); } },
        { "bct", [this](const TArray<FString>& parameters) { this->launchRessourceCreation(parameters); } },
        { "pic", [this](const TArray<FString>& parameters) { this->launchIncantation(parameters); } },
        { "pie", [this](const TArray<FString>& parameters) { this->launchEndIncantation(parameters); } },
        { "pdi", [this](const TArray<FString>& parameters) { this->launchDeathPlayer(parameters); } },
        { "tna", [this](const TArray<FString>& parameters) { this->launchTeamNameAddition(parameters); } },
        { "seg", [this](const TArray<FString>& parameters) { this->launchEndOfGame(parameters); } },
        { "enw", [this](const TArray<FString>& parameters) { this->launchEggLaying(parameters); } },
        { "edi", [this](const TArray<FString>& parameters) { this->launchKillEgg(parameters); } },
        { "pdr", [this](const TArray<FString>& parameters) { this->launchRessourceDropping(parameters); } },
        { "pgt", [this](const TArray<FString>& parameters) { this->launchRessourceCollecting(parameters); } }
    })
{}

void UCommandHandler::launchEndOfGame(const TArray<FString>& parameters)
{
    FString teamName;

    if (parameters.Num() != 2)
    {
        return;
    }
    teamName = parameters[1];
    OnGameEndEvent.Broadcast(teamName);
}

void UCommandHandler::launchKillEgg(const TArray<FString>& parameters)
{
    UWorld* world = GetWorld();
    TArray<AActor*> actors;

    if (parameters.Num() != 2)
    {
        return;
    }
    UGameplayStatics::GetAllActorsOfClass(world, AEgg::StaticClass(), actors);
    for (AActor* actor : actors)
    {
        AEgg* egg = Cast<AEgg>(actor);
        if (egg->GetEggId() == parameters[1])
        {
            egg->KillEgg();
        }
    }
}

void UCommandHandler::initConnection()
{
    OnServerWelcomeEvent.Broadcast();
}

void UCommandHandler::askForMapSize()
{
    OnServerConnectionEnd.Broadcast();
}

void UCommandHandler::handleCommand(const FString& command)
{
    FString commandKey;
    TArray<FString> parameters;

    commandKey = command.Left(3);
    command.ParseIntoArray(parameters, TEXT(" "), true);

    if (m_commandMap.Contains(commandKey))
    {
        m_commandMap[commandKey](parameters);
    } else if (m_connectionState > 0)
    {
        m_connectionState--;
        if (command.Contains("WELCOME", ESearchCase::IgnoreCase))
        {
            initConnection();
        }
        if (m_connectionState == 0)
        {
            askForMapSize();
        }
    }
}

void UCommandHandler::launchTeamNameAddition(const TArray<FString>& parameters)
{
    FString teamName;

    if (parameters.Num() != 2)
    {
        return;
    }
    teamName = parameters[1];
    OnTeamNameEvent.Broadcast(teamName);
}

void UCommandHandler::launchEggLaying(const TArray<FString>& parameters)
{
    FString eggId, playerId;

    if (parameters.Num() != 5)
    {
        return;
    }
    eggId = parameters[1];
    playerId = parameters[2];
    OnEggLayingEvent.Broadcast(eggId, playerId);
}

void UCommandHandler::launchDeathPlayer(const TArray<FString>& parameters)
{
    FString id;

    if (parameters.Num() != 2)
    {
        return;
    }
    id = parameters[1];
    OnPlayerDeadEvent.Broadcast(id);
}

void UCommandHandler::launchRessourceCreation(const TArray<FString>& parameters)
{
    int32 x = 0, y = 0;
    int32 food = 0, linemate = 0, deraumere = 0, sibur = 0, mendiane = 0, phiras = 0, thystame = 0;

    if (parameters.Num() != 10)
    {
        return;
    }
    x = FCString::Atoi(*parameters[1]);
    y = FCString::Atoi(*parameters[2]);
    food = FCString::Atoi(*parameters[3]);
    linemate = FCString::Atoi(*parameters[4]);
    deraumere = FCString::Atoi(*parameters[5]);
    sibur = FCString::Atoi(*parameters[6]);
    mendiane = FCString::Atoi(*parameters[7]);
    phiras = FCString::Atoi(*parameters[8]);
    thystame = FCString::Atoi(*parameters[9]);

    if (x < 0 || x >= m_mapWidth)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ressource creation: Bee x position is not valid"));
        return;
    }
    if (y < 0 || y >= m_mapLength)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ressource creation: Bee y position is not valid"));
        return;
    }
    OnRessourceCreationEvent.Broadcast(x , y , food, linemate, deraumere, sibur, mendiane, phiras, thystame);
}

void UCommandHandler::launchIncantation(const TArray<FString>& parameters)
{
    int32 x = 0, y = 0;
    int32 level = 0;
    TArray<FString> playerIds;

    if (parameters.Num() < 4)
    {
        return;
    }
    x = FCString::Atoi(*parameters[1]);
    y = FCString::Atoi(*parameters[2]);
    level = FCString::Atoi(*parameters[3]);

    if (x < 0 || x >= m_mapWidth)
    {
        UE_LOG(LogTemp, Warning, TEXT("Incantation: Bee x position is not valid"));
        return;
    }
    if (y < 0 || y >= m_mapLength)
    {
        UE_LOG(LogTemp, Warning, TEXT("Incantation: Bee y position is not valid"));
        return;
    }
    if (level < 1)
    {
        UE_LOG(LogTemp, Warning, TEXT("Incantation: Bee level is not valid"));
        return;
    }
    for (int32 i = 4; i < parameters.Num(); i++)
    {
        playerIds.Add(parameters[i]);
    }
    for (auto& playerId : playerIds)
    {
        OnIncantationStartEvent.Broadcast(x, y, level, playerId);
    }
}

void UCommandHandler::launchEndIncantation(const TArray<FString>& parameters)
{
    int32 x = 0, y = 0;
    FString result;

    if (parameters.Num() != 4 && parameters.Num() != 5)
    {
        return;
    }
    x = FCString::Atoi(*parameters[1]);
    y = FCString::Atoi(*parameters[2]);
    if (parameters.Num() == 4)
    {
        result = parameters[3];
    } else if (parameters.Num() == 5)
    {
        result = parameters[4];
    }
    OnIncantationEndEvent.Broadcast(x, y, result);
}

void UCommandHandler::launchMapCreation(const TArray<FString>& parameters)
{
    if (m_isMapCreated == true || parameters.Num() != 3)
    {
        return;
    }
    m_mapWidth = FCString::Atoi(*parameters[1]);
	m_mapLength = FCString::Atoi(*parameters[2]);
    if (m_mapWidth <= 0 || m_mapLength <= 0)
    {
        m_mapWidth = 0;
        m_mapLength = 0;
        return;
    }
    m_isMapCreated = true;
    OnMapCreationEvent.Broadcast(m_mapWidth, m_mapLength);
}

void UCommandHandler::launchPlayerConnection(const TArray<FString>& parameters)
{
    FString id;
    int32 x = 0;
    int32 y = 0;
    int32 orientation = 0;
    int32 level = 0;
    FString team;

    if (parameters.Num() != 7)
    {
        return;
    }
    id = parameters[1];
    x = FCString::Atoi(*parameters[2]);
    y = FCString::Atoi(*parameters[3]);
    orientation = FCString::Atoi(*parameters[4]);
    level = FCString::Atoi(*parameters[5]);
    team = parameters[6];

    if (orientation < 1 || orientation > 4)
    {
        UE_LOG(LogTemp, Warning, TEXT("New Bee: Bee orientation is not valid"));
        return;
    }
    if (x < 0 || x >= m_mapWidth)
    {
        UE_LOG(LogTemp, Warning, TEXT("New Bee: Bee x position is not valid"));
        return;
    }
    if (y < 0 || y >= m_mapLength)
    {
        UE_LOG(LogTemp, Warning, TEXT("New Bee: Bee y position is not valid"));
        return;
    }
    if (level < 1)
    {
        UE_LOG(LogTemp, Warning, TEXT("New Bee: Bee level is not valid"));
        return;
    }
    OnPlayerConnectionEvent.Broadcast(id, x * m_grassBlockSize, y * m_grassBlockSize, orientation, level, team);
}

void UCommandHandler::launchPlayerPosition(const TArray<FString>& parameters)
{
    UWorld* World = GetWorld();
    int32 x = 0;
    int32 y = 0;
    int32 orientation = 0;

    if (parameters.Num() != 5)
    {
        return;
    }
    x = FCString::Atoi(*parameters[2]);
    y = FCString::Atoi(*parameters[3]);
    orientation = FCString::Atoi(*parameters[4]);

    if (orientation < 1 || orientation > 4)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player position: Bee orientation is not valid"));
        return;
    }
    if (x < 0 || x >= m_mapWidth)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player position: Bee x position is not valid"));
        return;
    }
    if (y < 0 || y >= m_mapLength)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player position: Bee y position is not valid"));
        return;
    }

    if (World)
    {
        TArray<AActor*> FoundActors;

        UGameplayStatics::GetAllActorsOfClass(World, ABee::StaticClass(), FoundActors);
        for (auto& Actor : FoundActors)
        {
            ABee* Bee = Cast<ABee>(Actor);
            if (Bee && Bee->GetBeeId() == parameters[1])
            {
                Bee->GoToPosition(x * m_grassBlockSize, y * m_grassBlockSize, orientation);
                break;
            }
        }
    }
}

void UCommandHandler::launchRessourceDropping(const TArray<FString>& parameters)
{
    UWorld* world = GetWorld();
    FString playerId;
    int32 ressourceType = 0;

    if (parameters.Num() != 3)
    {
        return;
    }
    playerId = parameters[1];
    ressourceType = FCString::Atoi(*parameters[2]);
    if (ressourceType < 0 || ressourceType > 6)
    {
        return;
    }
    if (world)
    {
        TArray<AActor*> FoundActors;

        UGameplayStatics::GetAllActorsOfClass(world, ABee::StaticClass(), FoundActors);
        for (auto& Actor : FoundActors)
        {
            ABee* Bee = Cast<ABee>(Actor);
            if (Bee && Bee->GetBeeId() == playerId)
            {
                FVector2D tilesNb = Bee->GetBeeTileNumber();
                OnRessourceDroppingEvent.Broadcast(tilesNb.X, tilesNb.Y, ressourceType);
                return;
            }
        }
    }
}

void UCommandHandler::launchRessourceCollecting(const TArray<FString>& parameters)
{
    UWorld* world = GetWorld();
    FString playerId;
    int32 ressourceType = 0;

    if (parameters.Num() != 3)
    {
        return;
    }
    playerId = parameters[1];
    ressourceType = FCString::Atoi(*parameters[2]);
    if (ressourceType < 0 || ressourceType > 6)
    {
        return;
    }
    if (world)
    {
        TArray<AActor*> FoundActors;

        UGameplayStatics::GetAllActorsOfClass(world, ABee::StaticClass(), FoundActors);
        for (auto& Actor : FoundActors)
        {
            ABee* Bee = Cast<ABee>(Actor);
            if (Bee && Bee->GetBeeId() == playerId)
            {
                FVector2D tilesNb = Bee->GetBeeTileNumber();
                OnRessourceCollectingEvent.Broadcast(tilesNb.X, tilesNb.Y, ressourceType);
                return;
            }
        }
    }
}

#include "CommandHandler.h"
#include "Kismet/GameplayStatics.h"
#include "../Bee/Bee.h"

/*static const TMap<FString, ECommandType> CommandMap = {
    { "msz", ECommandType::MAP_SIZE },
    { "bct", ECommandType::TILE_CONTENT },
    { "tna", ECommandType::NAME_OF_TEAM },
    { "pnw", ECommandType::PLAYER_CONNECTION },
    { "ppo", ECommandType::PLAYER_POSITION },
    { "plv", ECommandType::PLAYER_LEVEL },
    { "pin", ECommandType::PLAYER_INVENTORY },
    { "pex", ECommandType::EXPULSION },
    { "pbc", ECommandType::BROADCAST },
    { "pic", ECommandType::START_INCANTATION },
    { "pie", ECommandType::END_INCANTATION },
    { "pfk", ECommandType::EGG_LAYING },
    { "pdr", ECommandType::RESOURCE_DROPPING },
    { "pgt", ECommandType::RESOURCE_COLLECTING },
    { "pdi", ECommandType::PLAYER_DEATH },
    { "enw", ECommandType::EGG_LAYING_BY_PLAYER },
    { "ebo", ECommandType::PLAYER_CONNECTION_FOR_AN_EGG },
    { "edi", ECommandType::EGG_DEATH },
    { "sgt", ECommandType::TIME_UNIT_REQUEST },
    { "sst", ECommandType::TIME_UNIT_MODIFICATION },
    { "seg", ECommandType::END_OF_GAME },
    { "smg", ECommandType::MESSAGE_FROM_SERVER },
    { "suc", ECommandType::UNKNOWN_COMMAND },
    { "sbp", ECommandType::COMMAND_PARAMETER }
};*/

UCommandHandler::UCommandHandler() :
    m_commandMap({
        { "msz", [this](const TArray<FString>& parameters) { this->launchMapCreation(parameters); } },
        { "pnw", [this](const TArray<FString>& parameters) { this->launchPlayerConnection(parameters); } },
        { "ppo", [this](const TArray<FString>& parameters) { this->launchPlayerPosition(parameters); } },
        { "bct", [this](const TArray<FString>& parameters) { this->launchRessourceCreation(parameters); } },
        { "pic", [this](const TArray<FString>& parameters) { this->launchIncantation(parameters); } },
        { "pie", [this](const TArray<FString>& parameters) { this->launchEndIncantation(parameters); } },
        { "pdi", [this](const TArray<FString>& parameters) { this->launchDeathPlayer(parameters); } }
    })
{}

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

#include "ZappyGameInstance.h"

FString UZappyGameInstance::GetIP() const
{
    return IP;
}

int32 UZappyGameInstance::GetPort() const
{
    return Port;
}

void UZappyGameInstance::SetIP(FString NewIP)
{
    IP = NewIP;
}

void UZappyGameInstance::SetPort(int32 NewPort)
{
    Port = NewPort;
}

void UZappyGameInstance::SetWinningTeam(FString NewWinningTeam)
{
    WinningTeam = NewWinningTeam;
}

FString UZappyGameInstance::GetWinningTeam() const
{
    return WinningTeam;
}

void UZappyGameInstance::AddTeam(FString NewTeam)
{
    m_teams.Add(NewTeam);
}

TArray<FString> UZappyGameInstance::GetTeams() const
{
    return m_teams;
}

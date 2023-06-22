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

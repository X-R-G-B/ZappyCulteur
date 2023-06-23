#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZappyGameInstance.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UZappyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable, Category="Network Variable")
	FString GetIP() const;

	UFUNCTION(BlueprintCallable, Category="Network Variable")
	int32 GetPort() const;

	UFUNCTION(BlueprintCallable, Category="Network Variable")
	void SetIP(FString NewIP);

	UFUNCTION(BlueprintCallable, Category="Network Variable")
	void SetPort(int32 NewPort);

	UFUNCTION(BlueprintCallable, Category="EndGame")
	void SetWinningTeam(FString NewWinningTeam);

	UFUNCTION(BlueprintCallable, Category="EndGame")
	FString GetWinningTeam() const;

	UFUNCTION(BlueprintCallable, Category="Team")
	void AddTeam(FString NewTeam);

	UFUNCTION(BlueprintCallable, Category="Team")
	TArray<FString> GetTeams() const;

	private:

    FString IP = "localhost";
    int32 Port = 9999;
	FString WinningTeam = "Unknown";
	TArray<FString> m_teams;
};

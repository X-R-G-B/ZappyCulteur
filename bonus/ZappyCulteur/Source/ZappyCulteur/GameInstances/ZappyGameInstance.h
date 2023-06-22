#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZappyGameInstance.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UZappyGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintCallable, Category="Network")
	FString GetIP() const;

	UFUNCTION(BlueprintCallable, Category="Network")
	int32 GetPort() const;

	UFUNCTION(BlueprintCallable, Category="Network")
	void SetIP(FString NewIP);

	UFUNCTION(BlueprintCallable, Category="Network")
	void SetPort(int32 NewPort);

	private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network", meta = (AllowPrivateAccess = "true"))
    FString IP = "localhost";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network", meta = (AllowPrivateAccess = "true"))
    int32 Port = 9999;
};

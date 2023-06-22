#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BeeUpdater.generated.h"

USTRUCT(BlueprintType)
struct FIncantation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Incantation")
    int32 x;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Incantation")
    int32 y;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Incantation")
    int32 level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Incantation")
    FString playerId;
};

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API UBeeUpdater : public UObject
{
	GENERATED_BODY()

public:
	UBeeUpdater() = default;

    UFUNCTION(BlueprintCallable, Category = "Update")
    void startBeesIncantation(int32 x, int32 y, int32 level, FString playerId);

    UFUNCTION(BlueprintCallable, Category = "Update")
    void stopBeesIncantation(int32 x, int32 y, FString result);

    UFUNCTION(BlueprintCallable, Category = "Dead")
    void killBeeFromId(FString playerId);

private:
    void AddIncantationData(int32 x, int32 y, int32 level, FString playerId);
    void RemoveIncantationData(int32 x, int32 y, FString playerId);
    bool IsIncantationDataExist(int32 x, int32 y, FString playerId);
    int32 GetReachedBeeLevel(int32 x, int32 y, FString playerId);
    TArray<FIncantation> m_incantations;
};

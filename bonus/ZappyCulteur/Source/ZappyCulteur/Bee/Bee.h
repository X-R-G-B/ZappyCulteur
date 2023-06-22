#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/SoftObjectPtr.h"
#include "Bee.generated.h"

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API ABee : public APawn
{
	GENERATED_BODY()

public:
	ABee();

	UFUNCTION(BlueprintCallable, Category = "Bee")
	void InitBee(FString id, FString team, int32 level, int32 orientation, int32 x, int32 y);

	UFUNCTION(BlueprintCallable, Category = "Bee")
	FString GetBeeId() const;

	UFUNCTION(BlueprintCallable, Category = "Bee")
	FString GetBeeTeam() const;

	UFUNCTION(BlueprintCallable, Category = "Bee")
	int32 GetBeeLevel() const;

	UFUNCTION(BlueprintCallable, Category = "Bee")
	void SetBeeId(FString id);

	UFUNCTION(BlueprintCallable, Category = "Bee")
	void SetBeeTeam(FString team);

	UFUNCTION(BlueprintCallable, Category = "Bee")
	void SetBeeLevel(int32 level);

	UFUNCTION(BlueprintCallable, Category = "Bee")
	void GoToPosition(int32 x, int32 y, int32 orientation);

	UFUNCTION(BlueprintCallable, Category = "Bee")
	FVector2D GetBeeTileNumber() const;

	UFUNCTION(BlueprintCallable, Category = "Incantation")
	void StartIncantation();

	UFUNCTION(BlueprintCallable, Category = "Incantation")
	void StopIncantation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bee")
	TSoftObjectPtr<UParticleSystem> incantationParticule;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	static constexpr int32 m_beeHeightMin = 250;
	static constexpr int32 m_beeHeightMax = 400;
	FString m_beeId = "Unknow";
	FString m_beeTeam = "Unknow";
	int32 m_beeLevel = 1;
	int32 m_beeOrientation = 0;
	int32 m_grassBlockSize = 200;
	float m_beeHeight = 250;
	float m_beeSpeed = 400;
	FVector m_toGoPosition;
	bool m_isMoving = false;
	bool m_isIncantating = false;
	UParticleSystemComponent* m_IncantationEmitter;
};

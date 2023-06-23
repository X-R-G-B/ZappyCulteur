#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Egg.generated.h"

UCLASS()
class ZAPPYCULTEUR_API AEgg : public AActor
{
	GENERATED_BODY()
	
public:	
	AEgg();

	UFUNCTION(BlueprintCallable, Category = "Egg")
	void SetId(FString id);

	UFUNCTION(BlueprintCallable, Category = "Egg")
	FString GetEggId() const;

	UFUNCTION(BlueprintCallable, Category = "Egg")
	void KillEgg();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FString m_id;
};

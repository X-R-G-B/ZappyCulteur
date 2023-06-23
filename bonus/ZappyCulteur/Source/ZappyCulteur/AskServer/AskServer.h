#pragma once

#include "CoreMinimal.h"
#include "AskServer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAskServerForInfos, FString, messages);

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API UAskServer : public UObject
{
	GENERATED_BODY()

	public:
		UAskServer() = default;
	    ~UAskServer() = default;

		UFUNCTION(BlueprintCallable, Category = "Update")
		void update(float deltaTime);

	private:
		void askForBees();
		void askForRessources();

		UPROPERTY(BlueprintAssignable, Category = "Network")
		FAskServerForInfos askServerDelegate;

		float m_timeSinceLastAsk = 0;
};

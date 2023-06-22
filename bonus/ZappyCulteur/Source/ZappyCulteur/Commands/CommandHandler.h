#pragma once

#include "CoreMinimal.h"
#include "Containers/Map.h"
#include "UObject/NoExportTypes.h"
#include "CommandHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMapCreationDelegate, int32, width, int32, height);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FServerWelcome);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FServerConnectionEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FPlayerConnectionDelegate, FString, id, int32, x, int32, y, int32, orientation, int32, level, FString, team);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineParams(FRessourceCreationDelegate, int32, caseX, int32, caseY,
	int32, foodNb, int32, linemateNb, int32, deraumereNb,
	int32, siburNb, int32, mendianeNb, int32, phirasNb, int32, thystameNb);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FIncantationStartDelegate, int32, x, int32, y, int32, level, FString, playerId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIncantationEndDelegate, int32, x, int32, y, FString, result);

UENUM(BlueprintType)
enum class ECommandType 
{
	MAP_SIZE,
	TILE_CONTENT,
	NAME_OF_TEAM,
	PLAYER_CONNECTION,
	PLAYER_POSITION,
	PLAYER_LEVEL,
	PLAYER_INVENTORY,
	EXPULSION,
	BROADCAST,
	START_INCANTATION,
	END_INCANTATION,
	EGG_LAYING,
	RESOURCE_DROPPING,
	RESOURCE_COLLECTING,
	PLAYER_DEATH,
	EGG_LAYING_BY_PLAYER,
	PLAYER_CONNECTION_FOR_AN_EGG,
	EGG_DEATH,
	TIME_UNIT_REQUEST,
	TIME_UNIT_MODIFICATION,
	END_OF_GAME,
	MESSAGE_FROM_SERVER,
	UNKNOWN_COMMAND,
	COMMAND_PARAMETER
};

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API UCommandHandler : public UObject
{
	GENERATED_BODY()

	public:
		UCommandHandler();
	    ~UCommandHandler() = default;

		UFUNCTION(BlueprintCallable, Category = "Update")
		void handleCommand(const FString& command);

	private:
		void launchMapCreation(const TArray<FString>& parameters);
		void launchPlayerConnection(const TArray<FString>& parameters);
		void launchPlayerPosition(const TArray<FString>& parameters);
		void initConnection();
		void askForMapSize();
		void launchRessourceCreation(const TArray<FString>& parameters);
		void launchIncantation(const TArray<FString>& parameters);
		void launchEndIncantation(const TArray<FString>& parameters);

		const TMap<FString, TFunction<void(const TArray<FString>&)>> m_commandMap;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FMapCreationDelegate OnMapCreationEvent;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FPlayerConnectionDelegate OnPlayerConnectionEvent;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FServerWelcome OnServerWelcomeEvent;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FServerWelcome OnServerConnectionEnd;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FRessourceCreationDelegate OnRessourceCreationEvent;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FIncantationStartDelegate OnIncantationStartEvent;

		UPROPERTY(BlueprintAssignable, Category = "Update")
		FIncantationEndDelegate OnIncantationEndEvent;

		int32 m_mapWidth = 0;
		int32 m_mapLength = 0;
		int32 m_connectionState = 3;
		float m_grassBlockSize = 200;
		bool m_isMapCreated = false;
};

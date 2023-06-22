#pragma once

#include "CoreMinimal.h"
#include "Networking.h"
#include "Sockets.h"
#include "UObject/NoExportTypes.h"
#include "SocketSubsystem.h"
#include "Async/Async.h"
#include "NetworkManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnServerConnectionCompleted, bool, bIsConnected);

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API UNetworkManager : public UObject
{
	GENERATED_BODY()

	public:
		UNetworkManager() = default;
		~UNetworkManager();

		UPROPERTY(BlueprintAssignable, Category = "Network")
		FOnServerConnectionCompleted OnServerConnectionCompletedDelegate;

		UFUNCTION(BlueprintCallable, Category = "Network")
			void InitServerConnection(FString IPAddress, int32 Port);

		UFUNCTION(BlueprintCallable, Category = "Network")
			void Update();

		UFUNCTION(BlueprintCallable, Category = "Network")
			void SendMessageToServer(FString message);

		UFUNCTION(BlueprintCallable, Category = "Network")
			bool IsConnected();

		UFUNCTION(BlueprintCallable, Category = "Network")
			TArray<FString> GetMessages();
		
	private:
		void SendMessages();
		void ReceiveMessages();
		uint32 FStringToBytes(const FString& string, uint8* outBytes, int32 maxBufferSize);
		FString BytesToFString(const uint8* inBytes, int32 Count);

		FString m_serverIp = "127.0.0.1";
		int32 m_port = 9999;
		bool bIsConnected = false;

		TArray<FString> m_incomingMessages;
		TArray<FString> m_outgoingMessages;

		FSocket* m_serverSocket;
		ISocketSubsystem* m_socketSubsystem;
		FIPv4Address m_ipAddress;
};

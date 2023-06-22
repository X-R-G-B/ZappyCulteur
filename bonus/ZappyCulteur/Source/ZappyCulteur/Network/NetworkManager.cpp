#include "NetworkManager.h"
#include "CoreMinimal.h"

void UNetworkManager::InitServerConnection(FString IPAddress, int32 Port)
{
	m_port = Port;
	m_serverIp = IPAddress;
	m_socketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	m_serverSocket = m_socketSubsystem->CreateSocket(NAME_Stream, TEXT("serverSocket"), false);
	if (m_serverSocket == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket not created!"));
		return;
	}

	if (m_serverIp.Equals("localhost", ESearchCase::IgnoreCase))
	{
		m_serverIp = "127.0.0.1";
	}

	TSharedRef<FInternetAddr> serverAddr = m_socketSubsystem->CreateInternetAddr();
	FIPv4Address::Parse(m_serverIp, m_ipAddress);
	serverAddr->SetIp(m_ipAddress.Value);
	serverAddr->SetPort(m_port);
	FIPv4Endpoint Endpoint(m_ipAddress, Port);

	Async(EAsyncExecution::ThreadPool, [this, serverAddr]()
	{
		bool isConnected = m_serverSocket->Connect(*serverAddr);
		m_serverSocket->SetNonBlocking(true);
		bIsConnected = isConnected;
		Async(EAsyncExecution::TaskGraphMainThread, [this]()
		{
			OnServerConnectionCompletedDelegate.Broadcast(bIsConnected);
		});
	});
}

void UNetworkManager::Update()
{
	if (bIsConnected)
	{
		ReceiveMessages();
		SendMessages();
	}
}

void UNetworkManager::SendMessageToServer(FString message)
{
	if (bIsConnected && message.IsEmpty() == false)
	{
		if (message.EndsWith("\n") == false)
		{
			message += "\n";
		}
		m_outgoingMessages.Add(message);
	}
}

bool UNetworkManager::IsConnected()
{
	return bIsConnected;
}

TArray<FString> UNetworkManager::GetMessages()
{
	TArray<FString> messages = m_incomingMessages;
	m_incomingMessages.Empty();
	return messages;
}

void UNetworkManager::SendMessages()
{
	int32 bytesSent = 0;
	int32 bufferSize = 0;
	uint8* data = nullptr;

	for (const FString& message : m_outgoingMessages)
	{
		bufferSize = message.Len();
		data = new uint8[bufferSize];
		if (data == nullptr)
		{
			continue;
		}
		if (FStringToBytes(message, data, bufferSize) > 0)
		{
			m_serverSocket->Send(data, bufferSize, bytesSent);
		}
		delete[] data;
	}
	m_outgoingMessages.Empty();
}

UNetworkManager::~UNetworkManager()
{
	if (m_serverSocket != nullptr)
	{
		if (bIsConnected)
		{
			m_serverSocket->Close();
		}
		m_socketSubsystem->DestroySocket(m_serverSocket);
		m_serverSocket = nullptr;
		bIsConnected = false;
	}
}

void UNetworkManager::ReceiveMessages()
{
	int32 bytesRead = 0;
	uint32 size = 1024;
	uint8* data = nullptr;
	TArray<FString> messages;

	while (m_serverSocket->HasPendingData(size))
	{
		bytesRead = 0;
		data = new uint8[size];
		if (data == nullptr)
		{
			continue;
		}
		m_serverSocket->Recv(data, size, bytesRead);
		if (bytesRead > 0)
		{
			FString message = BytesToFString(data, bytesRead);
			messages.Empty();
			message.ParseIntoArray(messages, TEXT("\n"), true);
			for (const FString& msg : messages)
			{
				m_incomingMessages.Add(msg);
			}
		}
		delete[] data;
	}
}

uint32 UNetworkManager::FStringToBytes(const FString& string, uint8* outBytes, int32 maxBufferSize)
{
	int32 numBytes = 0;
	const TCHAR* currentChar = *string;

	while(numBytes < maxBufferSize && *currentChar != '\0')
	{
		outBytes[numBytes] = static_cast<uint8>(*currentChar);
		currentChar++;
		++numBytes;
	}
	return numBytes;
}

FString UNetworkManager::BytesToFString(const uint8* inBytes, int32 Count)
{
	FString result = "";

	for (int32 i = 0; i < Count; ++i)
	{
		TCHAR currentChar = static_cast<TCHAR>(inBytes[i]);
		result.AppendChar(currentChar);
		if (currentChar == '\0')
		{
			break;
		}
	}
	return result;
}

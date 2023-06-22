#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StaticMesh.h"
#include "ZappyMap.generated.h"

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API UZappyMap : public UObject
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "Map")
		bool InitMap(int32 width, int32 height);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrassMesh")
		TSoftObjectPtr<UStaticMesh> GrassMesh;

	private:
		void SpawnBlock(TSoftObjectPtr <UStaticMesh> mesh, FVector location);
		FVector m_grassSize = FVector(0, 0, 0);
		int32 m_width;
		int32 m_height;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StaticMesh.h"
#include "RessourceSpawner.generated.h"

UCLASS(Blueprintable)
class ZAPPYCULTEUR_API URessourcesSpawner : public UObject
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "RessourcesSpawner")
		void CreateRessources(int32 caseX, int32 caseY,
		int32 foodNb, int32 linemateNb, int32 deraumereNb,
		int32 siburNb, int32 mendianeNb, int32 phirasNb, int32 thystameNb);

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> FoodMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> LinemateMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> DeraumereMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> SiburMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> MendianeMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> PhirasMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		TSoftObjectPtr<UStaticMesh> ThystameMesh;

	private:
		void SpawnBlock(TSoftObjectPtr <UStaticMesh> mesh, FVector location, FVector scale);
		void CreateRessource(int32 caseX, int32 caseY, TSoftObjectPtr<UStaticMesh> mesh, FVector scale = FVector(1, 1, 1));
		float m_grassSize = 200;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/StaticMesh.h"
#include "RessourceSpawner.generated.h"

USTRUCT(BlueprintType)
struct FRessources
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	int32 m_caseX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	int32 m_caseY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	int32 m_ressourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	FVector m_location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ressource")
	UStaticMeshComponent* m_mesh;
};


UCLASS(Blueprintable)
class ZAPPYCULTEUR_API URessourcesSpawner : public UObject
{
	GENERATED_BODY()
	
	public:
		UFUNCTION(BlueprintCallable, Category = "RessourcesSpawner")
		void CreateRessources(int32 caseX, int32 caseY,
		int32 foodNb, int32 linemateNb, int32 deraumereNb,
		int32 siburNb, int32 mendianeNb, int32 phirasNb, int32 thystameNb);

		UFUNCTION(BlueprintCallable, Category = "RessourcesSpawner")
		void CollectRessources(int32 tilex, int32 tiley, int32 ressourceType);

		UFUNCTION(BlueprintCallable, Category = "RessourcesSpawner")
		void DropRessources(int32 tilex, int32 tiley, int32 ressourceType);

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
		void SpawnBlock(TSoftObjectPtr <UStaticMesh> mesh, FVector location,
		FVector scale, int32 ressourceType, int32 caseX, int32 caseY);
		void CreateRessource(int32 caseX, int32 caseY, TSoftObjectPtr<UStaticMesh> mesh,
		int32 ressourceType = 0, FVector scale = FVector(1, 1, 1));
		int32 CountRessources(int32 tilex, int32 tiley, int32 ressourceType);
		float m_grassSize = 200;
		TArray<FRessources> m_ressources;
};

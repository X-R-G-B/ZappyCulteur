#include "RessourceSpawner.h"

void URessourcesSpawner::CreateRessources(int32 caseX, int32 caseY,
	int32 foodNb, int32 linemateNb, int32 deraumereNb,
	int32 siburNb, int32 mendianeNb, int32 phirasNb, int32 thystameNb)
{
    for (int32 i = 0; i < foodNb; i++)
    {
        FVector scale = FVector(0.3, 0.3, 0.3);
        CreateRessource(caseX, caseY, FoodMesh, scale);
    }
    for (int32 i = 0; i < linemateNb; i++)
    {
        CreateRessource(caseX, caseY, LinemateMesh);
    }
    for (int32 i = 0; i < deraumereNb; i++)
    {
        CreateRessource(caseX, caseY, DeraumereMesh);
    }
    for (int32 i = 0; i < siburNb; i++)
    {
        CreateRessource(caseX, caseY, SiburMesh);
    }
    for (int32 i = 0; i < mendianeNb; i++)
    {
        CreateRessource(caseX, caseY, MendianeMesh);
    }
    for (int32 i = 0; i < phirasNb; i++)
    {
        CreateRessource(caseX, caseY, PhirasMesh);
    }
    for (int32 i = 0; i < thystameNb; i++)
    {
        CreateRessource(caseX, caseY, ThystameMesh);
    }
}

void URessourcesSpawner::CreateRessource(int32 caseX, int32 caseY, TSoftObjectPtr<UStaticMesh> mesh, FVector scale)
{
    float x = 0, y = 0;
    int32 grassSize = static_cast<int32>(m_grassSize);
    int32 grassOffset = grassSize / 2;

    if (caseX == 0)
    {
        x = FMath::RandRange(0, grassSize);
    } else {
        x = FMath::RandRange(caseX * grassSize, (caseX + 1) * grassSize);
    }
    if (caseY == 0)
    {
        y = FMath::RandRange(0, grassSize);
    } else {
        y = FMath::RandRange(caseY * grassSize, (caseY + 1) * grassSize);
    }

    x -= grassOffset;
    y -= grassOffset;

    FVector location = FVector(x, y, m_grassSize);
    SpawnBlock(mesh, location, scale);
}

void URessourcesSpawner::SpawnBlock(TSoftObjectPtr<UStaticMesh> mesh, FVector location, FVector scale)
{
    UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);
    meshComponent->SetStaticMesh(mesh.LoadSynchronous());
    meshComponent->SetWorldLocation(location);
    meshComponent->SetWorldScale3D(scale);
    meshComponent->RegisterComponent();
}

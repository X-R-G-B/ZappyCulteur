#include "RessourceSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void URessourcesSpawner::CreateRessources(int32 caseX, int32 caseY,
	int32 foodNb, int32 linemateNb, int32 deraumereNb,
	int32 siburNb, int32 mendianeNb, int32 phirasNb, int32 thystameNb)
{
    foodNb -= CountRessources(caseX, caseY, 0);
    linemateNb -= CountRessources(caseX, caseY, 1);
    deraumereNb -= CountRessources(caseX, caseY, 2);
    siburNb -= CountRessources(caseX, caseY, 3);
    mendianeNb -= CountRessources(caseX, caseY, 4);
    phirasNb -= CountRessources(caseX, caseY, 5);
    thystameNb -= CountRessources(caseX, caseY, 6);
    
    for (int32 i = 0; i < foodNb; i++)
    {
        FVector scale = FVector(0.3, 0.3, 0.3);
        CreateRessource(caseX, caseY, FoodMesh, 0, scale);
    }
    for (int32 i = 0; i < linemateNb; i++)
    {
        CreateRessource(caseX, caseY, LinemateMesh, 1);
    }
    for (int32 i = 0; i < deraumereNb; i++)
    {
        CreateRessource(caseX, caseY, DeraumereMesh, 2);
    }
    for (int32 i = 0; i < siburNb; i++)
    {
        CreateRessource(caseX, caseY, SiburMesh, 3);
    }
    for (int32 i = 0; i < mendianeNb; i++)
    {
        CreateRessource(caseX, caseY, MendianeMesh, 4);
    }
    for (int32 i = 0; i < phirasNb; i++)
    {
        CreateRessource(caseX, caseY, PhirasMesh, 5);
    }
    for (int32 i = 0; i < thystameNb; i++)
    {
        CreateRessource(caseX, caseY, ThystameMesh, 6);
    }
}

int32 URessourcesSpawner::CountRessources(int32 tilex, int32 tiley, int32 ressourceType)
{
    int32 ressourceCount = 0;
    for (int32 i = 0; i < m_ressources.Num(); i++)
    {
        if (m_ressources[i].m_caseX == tilex && m_ressources[i].m_caseY == tiley && m_ressources[i].m_ressourceType == ressourceType)
        {
            ressourceCount++;
        }
    }
    return ressourceCount;
}

void URessourcesSpawner::CreateRessource(int32 caseX, int32 caseY, TSoftObjectPtr<UStaticMesh> mesh, int32 ressourceType, FVector scale)
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
    SpawnBlock(mesh, location, scale, ressourceType, caseX, caseY);
}

void URessourcesSpawner::CollectRessources(int32 tilex, int32 tiley, int32 ressourceType)
{
    for (int32 i = 0; i < m_ressources.Num(); i++)
    {
        if (m_ressources[i].m_caseX == tilex && m_ressources[i].m_caseY == tiley && m_ressources[i].m_ressourceType == ressourceType)
        {
            m_ressources[i].m_mesh->DestroyComponent();
            m_ressources.RemoveAt(i);
            break;
        }
    }
}

void URessourcesSpawner::DropRessources(int32 tilex, int32 tiley, int32 ressourceType)
{
    TSoftObjectPtr<UStaticMesh> mesh;
    FVector scale = FVector(1, 1, 1);
    switch (ressourceType)
    {
    case 0:
        mesh = FoodMesh;
        scale = FVector(0.3, 0.3, 0.3);
        break;
    case 1:
        mesh = LinemateMesh;
        break;
    case 2:
        mesh = DeraumereMesh;
        break;
    case 3:
        mesh = SiburMesh;
        break;
    case 4:
        mesh = MendianeMesh;
        break;
    case 5:
        mesh = PhirasMesh;
        break;
    case 6:
        mesh = ThystameMesh;
        break;
    default:
        break;
    }
    CreateRessource(tilex, tiley, mesh, ressourceType, scale);
}

void URessourcesSpawner::SpawnBlock(TSoftObjectPtr<UStaticMesh> mesh, FVector location, FVector scale, int32 ressourceType, int32 caseX, int32 caseY)
{
    UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);
    meshComponent->SetStaticMesh(mesh.LoadSynchronous());
    meshComponent->SetWorldLocation(location);
    meshComponent->SetWorldScale3D(scale);
    meshComponent->RegisterComponent();
    
    FRessources ressource;
    ressource.m_caseX = caseX;
    ressource.m_caseY = caseY;
    ressource.m_ressourceType = ressourceType;
    ressource.m_location = location;
    ressource.m_mesh = meshComponent;
    m_ressources.Add(ressource);
    UE_LOG(LogTemp, Warning, TEXT("Registering ressources of type %d at %d %d"), ressourceType, ressource.m_caseX, ressource.m_caseY);
}

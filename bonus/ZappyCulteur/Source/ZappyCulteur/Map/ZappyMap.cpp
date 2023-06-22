#include "ZappyMap.h"

bool UZappyMap::InitMap(int32 width, int32 height)
{
    m_width = width;
    m_height = height;

    float xOffset = m_grassSize.X * width / 2;
    float yOffset = m_grassSize.Y * height / 2;

    m_grassSize = GrassMesh.LoadSynchronous()->GetBoundingBox().GetSize();

    for (int32 i = 0; i < width; ++i)
    {
        for (int32 j = 0; j < height; ++j)
        {
            SpawnBlock(GrassMesh, FVector(i * m_grassSize.X - xOffset, j * m_grassSize.Y - yOffset, 0));
        }
    }
    return true;
}

void UZappyMap::SpawnBlock(TSoftObjectPtr<UStaticMesh> mesh, FVector location)
{
    UStaticMeshComponent* meshComponent = NewObject<UStaticMeshComponent>(this);
    meshComponent->SetStaticMesh(mesh.LoadSynchronous());
    meshComponent->SetWorldLocation(location);
    meshComponent->RegisterComponent();
}

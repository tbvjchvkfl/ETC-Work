// Fill out your copyright notice in the Description page of Project Settings.

//Framework
#include "LevelObject/SpawnPoint.h"
#include "LevelObject/SpawnObjectPool.h"

// Engine
#include "Kismet/GameplayStatics.h"

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &ASpawnPoint::Spawn, 1.0f, true);
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnPoint::Spawn()
{
	if (!SpawnObjectPool)
	{
		SpawnObjectPool = Cast<ASpawnObjectPool>(UGameplayStatics::GetActorOfClass(GetWorld(), ObjectPoolClass));
	}
	
	if (SpawnObjectPool->bIsEnabledSpawn && SpawnObjectPool->CheckObjectPool())
	{
		SpawnObjectPool->UsePoolObject(GetActorLocation());
	}
}


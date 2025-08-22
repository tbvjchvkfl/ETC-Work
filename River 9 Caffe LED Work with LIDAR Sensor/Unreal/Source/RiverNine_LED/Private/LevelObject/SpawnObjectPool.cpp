// Fill out your copyright notice in the Description page of Project Settings.

// Framework
#include "LevelObject/SpawnObjectPool.h"

// Engine


ASpawnObjectPool::ASpawnObjectPool() : bIsEnabledSpawn(false)
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASpawnObjectPool::BeginPlay()
{
	Super::BeginPlay();
	InitializePool();
}

void ASpawnObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnObjectPool::InitializePool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	for (int i = 0; i < PoolSize; i++)
	{
		if (APawn* SpawnObject = GetWorld()->SpawnActor<APawn>(ObjectClass, GetActorLocation(), GetActorRotation(), SpawnParams))
		{
			SpawnObject->SetActorHiddenInGame(true);
			ObjectPool.Add(SpawnObject);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Index : %d"), i));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Null"));
		}
	}
	bIsEnabledSpawn = true;
}

APawn* ASpawnObjectPool::UsePoolObject(FVector SpawnLocation)
{
	if (ObjectPool.Num() > 0)
	{
		APawn* SpawnObject = ObjectPool[ObjectPool.Num() - 1];
		SpawnObject->SetActorHiddenInGame(false);
		SpawnObject->SetActorEnableCollision(true);
		SpawnObject->SetActorLocation(SpawnLocation);
		ObjectPool.RemoveAt(ObjectPool.Num() - 1);
		return SpawnObject;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No available objects in the pool!"));
		return nullptr;
	}
}

void ASpawnObjectPool::ReturnPoolObject(APawn* ReturnObject)
{
	if (ReturnObject)
	{
		ReturnObject->SetActorHiddenInGame(true);
		ReturnObject->SetActorEnableCollision(false);
		ObjectPool.Add(ReturnObject);
	}
}

bool ASpawnObjectPool::CheckObjectPool()
{
	if (ObjectPool.Num() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
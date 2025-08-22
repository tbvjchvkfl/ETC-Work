// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObjectPool.generated.h"


UCLASS()
class RIVERNINE_LED_API ASpawnObjectPool : public AActor
{
	GENERATED_BODY()
	
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	bool bIsEnabledSpawn;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	ASpawnObjectPool();
	bool CheckObjectPool();
	APawn* UsePoolObject(FVector SpawnLocation);
	void ReturnPoolObject(APawn* ReturnObject);

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APawn> ObjectClass;

	UPROPERTY(VisibleAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TArray<APawn*> ObjectPool;

	UPROPERTY(EditDefaultsOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	int PoolSize;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InitializePool();
};

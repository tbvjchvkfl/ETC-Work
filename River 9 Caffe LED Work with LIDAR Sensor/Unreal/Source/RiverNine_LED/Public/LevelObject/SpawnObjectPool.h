// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnObjectPool.generated.h"

class AObjectBase;

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
	AObjectBase* UsePoolObject(FVector SpawnLocation);
	void ReturnPoolObject(AObjectBase* ReturnObject);

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AObjectBase> ObjectClass;

	UPROPERTY(VisibleAnywhere, Category = "Property", meta = (AllowPrivateAccess = "true"))
	TArray<AObjectBase*> ObjectPool;

	UPROPERTY(EditDefaultsOnly, Category = "Property", meta = (AllowPrivateAccess = "true"))
	int PoolSize;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InitializePool();
};

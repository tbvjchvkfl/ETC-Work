// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class ASpawnObjectPool;

UCLASS()
class RIVERNINE_LED_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property")
	TSubclassOf<ASpawnObjectPool> ObjectPoolClass;


	//==============================================================
	//=                          Function                          =
	//==============================================================
	ASpawnPoint();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY()
	FTimerHandle SpawnTimer;

	UPROPERTY()
	ASpawnObjectPool* SpawnObjectPool;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Spawn();
};

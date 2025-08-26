// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementLimitVolume.generated.h"

class UBoxComponent;

UCLASS()
class RIVERNINE_LED_API AMovementLimitVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	AMovementLimitVolume();
	FVector GetRandomPointInVolume() const;
private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property | Essential Data")
	UBoxComponent* CollisionBox;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

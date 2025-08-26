// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AnimalBase.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UFloatingPawnMovement;
class UUtilityComponent;

UCLASS()
class RIVERNINE_LED_API AAnimalBase : public APawn
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	AAnimalBase();
	FORCEINLINE UUtilityComponent* GetUtilityManager()const { return UtilityManager; }

protected:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PawnMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UUtilityComponent* UtilityManager;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

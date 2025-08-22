// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Component/UtilityComponent.h"
#include "Dory.generated.h"

class USphereComponent;
class USkeletalMeshComponent;
class UFloatingPawnMovement;

UCLASS()
class RIVERNINE_LED_API ADory : public APawn, public IUtilityInterface
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	ADory();
	virtual float CalculateActionScore(const FString& ActionName) const override;
	virtual void ExcuteAction(const FString& ActionName) override;

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Property | Essential Data", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data", meta = (AllowPrivateAccess = "true"))
	UUtilityComponent* UtilityManager;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

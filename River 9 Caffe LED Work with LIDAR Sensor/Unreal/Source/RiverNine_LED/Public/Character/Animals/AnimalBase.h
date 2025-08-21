// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AnimalBase.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class USkeletalMeshComponent;
class AAnimalController;
class UAnimalAnimInstance;

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
	void ObjectInteraction();

protected:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data")
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data")
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Property | Essential Data")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Base | Essential Data")
	AAnimalController* OwningController;

	UPROPERTY(VisibleAnywhere, Category = "Base | Essential Data")
	UAnimalAnimInstance* OwningAnimInstance;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void Interaction();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================



	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

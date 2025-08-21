// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UFloatingPawnMovement;
class UCapsuleComponent;

UCLASS()
class RIVERNINE_LED_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================



	//==============================================================
	//=                          Function                          =
	//==============================================================
	APlayerCharacter();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data")
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Essential Data")
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, Category = "Property | Essential Data")
	UFloatingPawnMovement* MovementComponent;


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


};

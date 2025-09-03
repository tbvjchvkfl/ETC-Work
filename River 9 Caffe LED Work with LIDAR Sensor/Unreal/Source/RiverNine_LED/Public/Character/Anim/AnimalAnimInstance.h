// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimalAnimInstance.generated.h"

class AAnimalBase;
class AAnimalController;

UCLASS()
class RIVERNINE_LED_API UAnimalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PROPERTY | State")
	bool Flee = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | Swim")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | Swim")
	FVector MoveDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | Swim")
	FVector PrevMoveDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PROPERTY | Swim")
	float SwimFrequency = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PROPERTY | Swim")
	float SwimAmplitude = 15.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | Essential Data")
	AAnimalBase* OwnerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | Essential Data")
	AAnimalController* OwnerController;

	// Procedural / IK
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FVector RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FVector RootLocationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FVector HeadEffectorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FRotator HeadRotationOffest;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FRotator TailRotationOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FRotator LeftSideFinRotationOffset;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "PROPERTY | IK")
	FRotator RightSideFinRotationOffset;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	float ElapsedTime = 0.0f;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void NativeInitializeAnimation()override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};

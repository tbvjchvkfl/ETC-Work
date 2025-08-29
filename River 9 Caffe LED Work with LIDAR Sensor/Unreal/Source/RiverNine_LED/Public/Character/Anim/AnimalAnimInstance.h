// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimalAnimInstance.generated.h"

class AAnimalBase;

UCLASS()
class RIVERNINE_LED_API UAnimalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Swim")
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float SwimFrequency = 6.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swim")
	float SwimAmplitude = 15.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Essential Data")
	AAnimalBase* OwnerCharacter;

	// Procedural / IK
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "IK")
	FVector RootLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "IK")
	FVector HeadEffectorLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "IK")
	FRotator TailRotationOffset;

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

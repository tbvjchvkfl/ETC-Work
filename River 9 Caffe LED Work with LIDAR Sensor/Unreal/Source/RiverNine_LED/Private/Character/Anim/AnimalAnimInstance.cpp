// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Anim/AnimalAnimInstance.h"
#include "Character/Animals/AnimalBase.h"
#include "Character/Controller/AnimalController.h"

// Engine
#include "Components/SkeletalMeshComponent.h"

void UAnimalAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnimalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<AAnimalBase>(TryGetPawnOwner());
	OwnerController = Cast<AAnimalController>(OwnerCharacter->GetController());
}

void UAnimalAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAnimalBase>(TryGetPawnOwner());
	}
	if (!OwnerController)
	{
		//OwnerController = Cast<AAnimalController>(OwnerCharacter->GetController());
	}
	if (OwnerCharacter)
	{
		ElapsedTime += DeltaSeconds;
		if (ElapsedTime > 2 * PI)
		{
			ElapsedTime = FMath::Fmod(ElapsedTime, 2 * PI);
		}
		RootLocation = OwnerCharacter->GetActorLocation();
		MoveDirection = Velocity.GetSafeNormal();
	}
}

void UAnimalAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (OwnerCharacter)
	{
		FVector MoveDir = Velocity.GetSafeNormal();
		if (!MoveDir.IsNearlyZero())
		{
			HeadEffectorLocation = OwnerCharacter->GetActorLocation() + MoveDir * 50.f;
		}

		float SpeedBasedSwimFrequency = SwimFrequency * Velocity.Size();

		float BodySway = FMath::Sin(ElapsedTime * SpeedBasedSwimFrequency * 0.05f) * 5.0f;
		RootLocationOffset = FVector(0.0f, BodySway, 0.0f);

		float HeadSway = FMath::Sin((ElapsedTime * SpeedBasedSwimFrequency * 0.5f) + PI * 0.5f) * SwimAmplitude;
		HeadRotationOffest = FRotator(0.0f, HeadSway, 0.0f);
		
		float TailSway = FMath::Sin(ElapsedTime * SpeedBasedSwimFrequency/* * 0.01f*/) * SwimAmplitude;
		TailRotationOffset = FRotator(0.f, TailSway, 0.f);

		float SideFinSway = FMath::Sin(ElapsedTime * Velocity.Size() * 0.1f) * 15.0f;
		LeftSideFinRotationOffset = FRotator(SideFinSway, SideFinSway, 0.0f);
		RightSideFinRotationOffset = FRotator(-SideFinSway, -SideFinSway, 0.0f);
	}
}

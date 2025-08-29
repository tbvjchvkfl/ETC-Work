// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Anim/AnimalAnimInstance.h"
#include "Character/Animals/AnimalBase.h"

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
}

void UAnimalAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ElapsedTime += DeltaSeconds;

	if (!OwnerCharacter)
	{
		OwnerCharacter = Cast<AAnimalBase>(TryGetPawnOwner());
	}
	if (OwnerCharacter)
	{
        RootLocation = OwnerCharacter->GetActorLocation();
        Velocity = OwnerCharacter->GetVelocity();

        FVector MoveDir = Velocity.GetSafeNormal();
        if (!MoveDir.IsNearlyZero())
        {
            HeadEffectorLocation = OwnerCharacter->GetActorLocation() + MoveDir * 50.f;
        }

        float Sway = FMath::Sin(ElapsedTime * SwimFrequency) * SwimAmplitude;
        TailRotationOffset = FRotator(0.f, Sway, 0.f);
	}
}

void UAnimalAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

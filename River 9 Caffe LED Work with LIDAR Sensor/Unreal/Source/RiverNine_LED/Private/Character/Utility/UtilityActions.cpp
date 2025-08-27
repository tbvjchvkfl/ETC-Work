// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Utility/UtilityActions.h"
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "LevelObject/MovementLimitVolume.h"

// Engine
#include "GameFramework/FloatingPawnMovement.h"
#include "BehaviorTree/BlackboardComponent.h"

// MoveAction

void UUtilityMoveAction::InitMoveAction()
{
	if (UUtilityComponent* UtilityManager = Cast<UUtilityComponent>(GetOuter()))
	{
		Owner = Cast<AAnimalBase>(UtilityManager->GetOwner());
		if (Owner)
		{
			MoveComp = Owner->GetFloatingMovementComponent();
		}
	}
	TargetLocation = FVector::ZeroVector;
	ActionName = FName(TEXT("Move Action"));
	BaseScore = 0.1f;
}

void UUtilityMoveAction::SetTargetLocation()
{
	if (AMovementLimitVolume* MovementVolume = Owner->GetMovementLimitVolume())
	{
		TargetLocation = MovementVolume->GetRandomPointInVolume();
	}
	else
	{
		TargetLocation = FVector::ZeroVector;
	}
}

bool UUtilityMoveAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), TargetLocation) <= 100.0f)
	{
		return true;
	}
	return false;
}

float UUtilityMoveAction::CalculateActionScore()
{
	return BaseScore;
}

void UUtilityMoveAction::ExecuteAction()
{
	if (TargetLocation != FVector::ZeroVector)
	{
		FVector MoveDirection = (TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
		MoveComp->MaxSpeed = 200.0f;
		MoveComp->AddInputVector(MoveDirection * Owner->MoveSpeed);

		if (!MoveDirection.IsNearlyZero())
		{
			FRotator MoveRotation = MoveDirection.Rotation();
			MoveRotation.Roll = Owner->GetActorRotation().Roll;
			Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), MoveRotation, GetWorld()->GetDeltaSeconds(), 2.0f));
		}
	}
}





// Flee Action

void UUtilityFleeAction::InitFleeAction()
{
	if (UUtilityComponent* UtilityManager = Cast<UUtilityComponent>(GetOuter()))
	{
		Owner = Cast<AAnimalBase>(UtilityManager->GetOwner());
		if (Owner)
		{
			MoveComp = Owner->GetFloatingMovementComponent();
		}
	}
	TargetLocation = FVector::ZeroVector;
	ActionName = FName(TEXT("Flee Action"));
	BaseScore = 0.0f;
}

void UUtilityFleeAction::SetTargetLocation()
{
	if (AMovementLimitVolume* MovementVolume = Owner->GetMovementLimitVolume())
	{
		TargetLocation = MovementVolume->GetRandomPointInVolume();
	}
	else
	{
		TargetLocation = FVector::ZeroVector;
	}
}

bool UUtilityFleeAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), TargetLocation) <= 100.0f)
	{
		if (UUtilityComponent* UtilityManager = Cast<UUtilityComponent>(GetOuter()))
		{
			Owner->bIsInteraction = false;
		}
		return true;
	}
	return false;
}

float UUtilityFleeAction::CalculateActionScore()
{
	if (Owner->bIsInteraction)
	{
		BaseScore = 1.0f;
	}
	else
	{
		BaseScore = 0.0f;
	}
	return BaseScore;
}

void UUtilityFleeAction::ExecuteAction()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Flee Action"));
	if (TargetLocation != FVector::ZeroVector)
	{
		FVector MoveDirection = (TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
		MoveComp->MaxSpeed = 1200.0f;
		MoveComp->AddInputVector(MoveDirection * Owner->FleeSpeed);

		if (!MoveDirection.IsNearlyZero())
		{
			FRotator MoveRotation = MoveDirection.Rotation();
			MoveRotation.Roll = Owner->GetActorRotation().Roll;
			Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), MoveRotation, GetWorld()->GetDeltaSeconds(), 2.0f));
		}
	}
}

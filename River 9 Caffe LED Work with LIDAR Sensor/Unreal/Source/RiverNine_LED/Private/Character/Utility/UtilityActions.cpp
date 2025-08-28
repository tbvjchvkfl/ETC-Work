// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Utility/UtilityActions.h"
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "LevelObject/MovementLimitVolume.h"

// Engine
#include "GameFramework/FloatingPawnMovement.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

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
	BaseScore = 0.0f;
	if (Owner->bIsInteraction)
	{
		BaseScore = 1.0f;
		if (Owner->InteractionCount != 0 && Owner->InteractionCount % 3 == 0)
		{
			BaseScore = 0.0f;
		}
	}
	return BaseScore;
}

void UUtilityFleeAction::ExecuteAction()
{
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



// Hide Action

void UUtilityHideAction::InitHideAction()
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
	ActionName = FName(TEXT("Hide Action"));
	BaseScore = 0.0f;
}

void UUtilityHideAction::SetTargetLocation()
{
	if (Owner)
	{
		TargetLocation = Owner->SetHideLocation();
	}
	else
	{
		TargetLocation = FVector::ZeroVector;
	}
}

bool UUtilityHideAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), TargetLocation) <= 100.0f)
	{
		Owner->InteractionCount++;
		return true;
	}
	return false;
}

float UUtilityHideAction::CalculateActionScore()
{
	if (Owner->InteractionCount != 0 && Owner->InteractionCount % 3 == 0)
	{
		BaseScore = 1.0f;
	}
	else
	{
		BaseScore = 0.0f;
	}
	return BaseScore;
}

void UUtilityHideAction::ExecuteAction()
{
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

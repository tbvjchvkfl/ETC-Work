// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Utility/UtilityActions.h"
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "LevelObject/MovementLimitVolume.h"
#include "Character/Anim/AnimalAnimInstance.h"

// Engine
#include "GameFramework/FloatingPawnMovement.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

// MoveAction

void UUtilityMoveAction::InitAction(AAnimalBase* owner)
{
	Owner = owner;
	if (Owner)
	{
		MoveComp = Owner->GetFloatingMovementComponent();
		ActionName = FName(TEXT("Move Action"));
		BaseScore = 0.1f;
	}
}

void UUtilityMoveAction::SetTargetLocation()
{
	if (Owner)
	{
		if (AMovementLimitVolume* MovementVolume = Owner->GetMovementLimitVolume())
		{
			Owner->TargetLocation = MovementVolume->GetRandomPointInVolume();
		}
		else
		{
			Owner->TargetLocation = FVector::ZeroVector;
		}
	}
}

bool UUtilityMoveAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), Owner->TargetLocation) <= 100.0f)
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
	if (!Owner || Owner->TargetLocation == FVector::ZeroVector) return;

	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	FVector TargetVelocity = DesiredDir * Owner->MaxMoveSpeed;

	FVector VelocityDiff = TargetVelocity - Owner->CurrentVelocity;

	float AccelRate = (FVector::DotProduct(VelocityDiff, DesiredDir) > 0) ? Owner->MoveAcceleration	: Owner->Deceleration;

	FVector AccelStep = VelocityDiff.GetClampedToMaxSize(AccelRate * GetWorld()->GetDeltaSeconds());

	Owner->CurrentVelocity += AccelStep;
	Owner->AddActorWorldOffset(Owner->CurrentVelocity * GetWorld()->GetDeltaSeconds(), true);

	if (!Owner->CurrentVelocity.IsNearlyZero())
	{
		FRotator DesiredRot = Owner->CurrentVelocity.Rotation();
		DesiredRot.Roll = Owner->GetActorRotation().Roll;
		Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), DesiredRot, GetWorld()->GetDeltaSeconds(), 30.0f));
	}

	if (UAnimalAnimInstance* AnimInst = Cast<UAnimalAnimInstance>(Owner->GetPawnMesh()->GetAnimInstance()))
	{
		AnimInst->Velocity = Owner->CurrentVelocity;
	}
}





// Flee Action

void UUtilityFleeAction::InitAction(AAnimalBase* owner)
{
	Owner = owner;
	if (Owner)
	{
		MoveComp = Owner->GetFloatingMovementComponent();
		ActionName = FName(TEXT("Flee Action"));
		BaseScore = 0.0f;
	}
}

void UUtilityFleeAction::SetTargetLocation()
{
	if (Owner)
	{
		if (AMovementLimitVolume* MovementVolume = Owner->GetMovementLimitVolume())
		{
			Owner->TargetLocation = MovementVolume->GetRandomPointInVolume();
		}
		else
		{
			Owner->TargetLocation = FVector::ZeroVector;
		}
	}
}

bool UUtilityFleeAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), Owner->TargetLocation) <= 100.0f)
	{
		Owner->bIsInteraction = false;
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
	if (!Owner || Owner->TargetLocation == FVector::ZeroVector) return;

	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	FVector TargetVelocity = DesiredDir * Owner->MaxFleeSpeed;

	FVector VelocityDiff = TargetVelocity - Owner->CurrentVelocity;

	float AccelRate = (FVector::DotProduct(VelocityDiff, DesiredDir) > 0) ? Owner->FleeAcceleration : Owner->Deceleration;

	FVector AccelStep = VelocityDiff.GetClampedToMaxSize(AccelRate * GetWorld()->GetDeltaSeconds());

	Owner->CurrentVelocity += AccelStep;
	Owner->AddActorWorldOffset(Owner->CurrentVelocity * GetWorld()->GetDeltaSeconds(), true);

	if (!Owner->CurrentVelocity.IsNearlyZero())
	{
		FRotator DesiredRot = Owner->CurrentVelocity.Rotation();
		DesiredRot.Roll = Owner->GetActorRotation().Roll;
		Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), DesiredRot, GetWorld()->GetDeltaSeconds(), 50.0f));
	}

	if (UAnimalAnimInstance* AnimInst = Cast<UAnimalAnimInstance>(Owner->GetPawnMesh()->GetAnimInstance()))
	{
		AnimInst->Velocity = Owner->CurrentVelocity;
	}
}



// Hide Action

void UUtilityHideAction::InitAction(AAnimalBase* owner)
{
	Owner = owner;
	if (Owner)
	{
		MoveComp = Owner->GetFloatingMovementComponent();
		Owner->TargetLocation = FVector::ZeroVector;
		ActionName = FName(TEXT("Hide Action"));
		BaseScore = 0.0f;
	}
}

void UUtilityHideAction::SetTargetLocation()
{
	if (Owner)
	{
		Owner->TargetLocation = Owner->SetHideLocation();
	}
	else
	{
		Owner->TargetLocation = FVector::ZeroVector;
	}
}

bool UUtilityHideAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), Owner->TargetLocation) <= 100.0f)
	{
		Owner->bIsInteraction = false;
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
	if (!Owner || Owner->TargetLocation == FVector::ZeroVector) return;

	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	FVector TargetVelocity = DesiredDir * Owner->MaxFleeSpeed;

	FVector VelocityDiff = TargetVelocity - Owner->CurrentVelocity;

	float AccelRate = (FVector::DotProduct(VelocityDiff, DesiredDir) > 0) ? Owner->FleeAcceleration : Owner->Deceleration;

	FVector AccelStep = VelocityDiff.GetClampedToMaxSize(AccelRate * GetWorld()->GetDeltaSeconds());

	Owner->CurrentVelocity += AccelStep;
	Owner->AddActorWorldOffset(Owner->CurrentVelocity * GetWorld()->GetDeltaSeconds(), true);

	if (!Owner->CurrentVelocity.IsNearlyZero())
	{
		FRotator DesiredRot = Owner->CurrentVelocity.Rotation();
		DesiredRot.Roll = Owner->GetActorRotation().Roll;
		Owner->SetActorRotation(FMath::RInterpTo(Owner->GetActorRotation(), DesiredRot, GetWorld()->GetDeltaSeconds(), 1.5f));
	}

	if (UAnimalAnimInstance* AnimInst = Cast<UAnimalAnimInstance>(Owner->GetPawnMesh()->GetAnimInstance()))
	{
		AnimInst->Velocity = Owner->CurrentVelocity;
	}
}

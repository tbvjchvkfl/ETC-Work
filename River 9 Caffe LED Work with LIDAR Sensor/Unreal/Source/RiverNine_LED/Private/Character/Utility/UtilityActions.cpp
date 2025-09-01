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
		//TargetLocation = FVector::ZeroVector;
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

	float AccelRate = (FVector::DotProduct(VelocityDiff, DesiredDir) > 0) ? Owner->Acceleration	: Owner->Deceleration;

	FVector AccelStep = VelocityDiff.GetClampedToMaxSize(AccelRate * GetWorld()->GetDeltaSeconds());

	Owner->CurrentVelocity += AccelStep;
	Owner->AddActorWorldOffset(Owner->CurrentVelocity * GetWorld()->GetDeltaSeconds(), true);



	//if (Owner && Owner->TargetLocation != FVector::ZeroVector)
	//{
	//	if (Owner->CurrentVelocity.IsNearlyZero())
	//	{
	//		Owner->CurrentVelocity = FVector::ZeroVector;
	//	}

	//	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	//	FVector DesiredVelocity = DesiredDir * Owner->MoveSpeed * 100.f; // 속도 스케일

	//	Owner->CurrentVelocity = FMath::VInterpTo(Owner->CurrentVelocity, DesiredVelocity, GetWorld()->GetDeltaSeconds(), 0.8f);

	//	Owner->AddActorWorldOffset(Owner->CurrentVelocity * GetWorld()->GetDeltaSeconds(), true);
	//}

	/*if (TargetLocation != FVector::ZeroVector)
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
	}*/

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
		//TargetLocation = FVector::ZeroVector;
		ActionName = FName(TEXT("Flee Action"));
		BaseScore = 0.0f;
	}
}

void UUtilityFleeAction::SetTargetLocation()
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

bool UUtilityFleeAction::CompleteAction()
{
	if (FVector::Dist(Owner->GetActorLocation(), Owner->TargetLocation) <= 100.0f)
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
	if (!Owner || Owner->TargetLocation == FVector::ZeroVector) return;

	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	FVector DesiredVelocity = DesiredDir * Owner->MoveSpeed * 500.f; // 속도 스케일

	Owner->CurrentVelocity = FMath::VInterpTo(Owner->CurrentVelocity, DesiredVelocity, GetWorld()->GetDeltaSeconds(), 0.8f);

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
	/*if (TargetLocation != FVector::ZeroVector)
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
	}*/
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
	if (!Owner || Owner->TargetLocation == FVector::ZeroVector) return;

	FVector DesiredDir = (Owner->TargetLocation - Owner->GetActorLocation()).GetSafeNormal();
	FVector DesiredVelocity = DesiredDir * Owner->MoveSpeed * 500.f; // 속도 스케일

	Owner->CurrentVelocity = FMath::VInterpTo(Owner->CurrentVelocity, DesiredVelocity, GetWorld()->GetDeltaSeconds(), 0.8f);

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

// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "Character/Utility/UtilityActionBase.h"

// Engine
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


AAnimalBase::AAnimalBase() : bIsInteraction(false), MoveSpeed(1.0f), FleeSpeed(10.0f)
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = SphereCollision;

	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pawn Mesh"));
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PawnMesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	MovementComponent->MaxSpeed = 200.0f;
	UtilityManager = CreateDefaultSubobject<UUtilityComponent>(TEXT("Utility Manager"));
}

void AAnimalBase::TriggerFleeAction()
{
	if (UtilityManager)
	{
		for (UUtilityActionBase* Action : UtilityManager->AvailableActions)
		{
			if (Action->ActionName == FName(TEXT("Flee Action")))
			{
				UtilityManager->ForceExecuteAction(Action);
				bIsInteraction = true;
				break;
			}
		}
	}
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


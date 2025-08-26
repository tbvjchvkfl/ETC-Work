// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"

// Engine
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


AAnimalBase::AAnimalBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	RootComponent = SphereCollision;

	PawnMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pawn Mesh"));
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PawnMesh->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
	UtilityManager = CreateDefaultSubobject<UUtilityComponent>(TEXT("Utility Manager"));
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


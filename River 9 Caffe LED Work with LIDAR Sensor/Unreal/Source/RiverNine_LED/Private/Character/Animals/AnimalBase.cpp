// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/AnimalBase.h"
#include "Character/Controller/AnimalController.h"
#include "Character/Anim/AnimalAnimInstance.h"

// Engine
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AAnimalBase::AAnimalBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAnimalController::StaticClass();
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	
	OwningController = Cast<AAnimalController>(GetController());
	OwningAnimInstance = Cast<UAnimalAnimInstance>(MeshComponent->GetAnimInstance());
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalBase::ObjectInteraction()
{
	Interaction();
}

void AAnimalBase::Interaction()
{

}
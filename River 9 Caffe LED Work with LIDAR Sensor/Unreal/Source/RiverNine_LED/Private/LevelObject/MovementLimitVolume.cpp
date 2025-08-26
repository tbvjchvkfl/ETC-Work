// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "LevelObject/MovementLimitVolume.h"

// Engine
#include "Components/BoxComponent.h"

AMovementLimitVolume::AMovementLimitVolume()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	RootComponent = CollisionBox;
}

FVector AMovementLimitVolume::GetRandomPointInVolume() const
{
	if (!CollisionBox) return FVector::ZeroVector;

	FVector Origin = CollisionBox->Bounds.Origin;
	FVector Extent = CollisionBox->Bounds.BoxExtent;

	return Origin + FVector(
		FMath::FRandRange(-Extent.X, Extent.X),
		FMath::FRandRange(-Extent.Y, Extent.Y),
		FMath::FRandRange(-Extent.Z, Extent.Z)
	);
}

void AMovementLimitVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovementLimitVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


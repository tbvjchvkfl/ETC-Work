// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "LevelObject/HideObject.h"

// Engine
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

AHideObject::AHideObject()
{
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	RootComponent = DefaultSceneComponent;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(DefaultSceneComponent);
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(DefaultSceneComponent);
	SphereColiision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereColiision->SetupAttachment(DefaultSceneComponent);
}

void AHideObject::BeginPlay()
{
	Super::BeginPlay();
}

void AHideObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


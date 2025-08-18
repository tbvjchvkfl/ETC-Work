// Fill out your copyright notice in the Description page of Project Settings.

// Framework
#include "Character/ObjectBase.h"

// Engine

AObjectBase::AObjectBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AObjectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjectBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
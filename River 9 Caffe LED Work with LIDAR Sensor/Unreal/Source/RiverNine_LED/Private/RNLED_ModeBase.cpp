// Fill out your copyright notice in the Description page of Project Settings.


#include "RNLED_ModeBase.h"

ARNLED_ModeBase::ARNLED_ModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARNLED_ModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ARNLED_ModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
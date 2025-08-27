// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Level/LS_Ocean.h"
#include "Character/Controller/PlayerCharacterController.h"
#include "Character/Animals/AnimalBase.h"

// Engine

ALS_Ocean::ALS_Ocean()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALS_Ocean::BeginPlay()
{
	Super::BeginPlay();
	PCController = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}

void ALS_Ocean::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MouseInteraction();
}

void ALS_Ocean::MouseInteraction()
{
	if (PCController)
	{
		FVector WorldLocation, WorldDirection;
		PCController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		FHitResult Hit;
		FVector StartPoint = WorldLocation;
		FVector EndPoint = StartPoint + (WorldDirection * 10000.0f);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams))
		{
			if (AAnimalBase* InteractionObject = Cast<AAnimalBase>(Hit.GetActor()))
			{
				GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Blue, TEXT("Interaction!!!!!"));
				InteractionObject->TriggerFleeAction();
			}
		}
	}
}

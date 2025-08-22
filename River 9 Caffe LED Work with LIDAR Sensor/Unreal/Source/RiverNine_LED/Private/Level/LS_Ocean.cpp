// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Level/LS_Ocean.h"
#include "Character/Controller/PlayerCharacterController.h"

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
	//MouseInteraction();
}

void ALS_Ocean::MouseInteraction()
{
	if (PCController)
	{
		FVector WorldLocation, WorldDirection;
		PCController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

		FHitResult Hit;
		FVector StartPoint = WorldLocation;
		FVector EndPoint = StartPoint + (WorldDirection * 1000.0f);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(Hit, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, CollisionParams))
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Interaction : %s"), *Hit.GetActor()->GetName()));
			if (APawn* InteractionObject = Cast<APawn>(Hit.GetActor()))
			{
				GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Blue, FString::Printf(TEXT("Animal Interaction : %s"), *InteractionObject->GetName()));
				//InteractionObject->ObjectInteraction();
			}
		}
	}
}

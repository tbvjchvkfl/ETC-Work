// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "Character/Utility/UtilityActionBase.h"
#include "LevelObject/HideObject.h"

// Engine
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"


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
		InteractionCount++;
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

FVector AAnimalBase::SetHideLocation()
{
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Hide Object"), Actors);
	float MaxDistance = FLT_MAX;
	AActor* SelectedActor = nullptr;
	for (auto Actor : Actors)
	{
		float TargetDistance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
		if (MaxDistance > TargetDistance)
		{
			MaxDistance = TargetDistance;
			SelectedActor = Actor;
		}
	}
	AHideObject* HideObj = Cast<AHideObject>(SelectedActor);
	return HideObj->GetActorLocation();
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


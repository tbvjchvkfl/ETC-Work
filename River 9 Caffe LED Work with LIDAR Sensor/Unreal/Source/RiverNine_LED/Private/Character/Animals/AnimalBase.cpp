// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"
#include "Character/Utility/UtilityActionBase.h"
#include "LevelObject/HideObject.h"
#include "LevelObject/MovementLimitVolume.h"

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

bool AAnimalBase::CheckObstacleTargetLocation()
{
	bool ReturnValue = false;
	FHitResult Hit;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 100.0f;
	FCollisionQueryParams ColParams;
	ColParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, ColParams))
	{
		if (Hit.bBlockingHit)
		{
			ReturnValue = true;
		}
	}
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);
	return ReturnValue;
}

void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	MovementLimitVolume = Cast<AMovementLimitVolume>(UGameplayStatics::GetActorOfClass(GetWorld(), AMovementLimitVolume::StaticClass()));

	SphereCollision->OnBeginCursorOver.AddDynamic(this, &AAnimalBase::OnBeginMouseOver);
}

void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalBase::OnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Touch"));
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


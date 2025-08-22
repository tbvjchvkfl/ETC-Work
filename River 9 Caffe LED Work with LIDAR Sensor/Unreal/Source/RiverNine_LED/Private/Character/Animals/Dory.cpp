// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Animals/Dory.h"
#include "Component/UtilityComponent.h"

// Engine
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


ADory::ADory()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	UtilityManager = CreateDefaultSubobject<UUtilityComponent>(TEXT("UtilityManager"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	UtilityManager->ActionList.Add({ "Eat",  0.0f, this });
	UtilityManager->ActionList.Add({ "Flee", 0.0f, this });
}

float ADory::CalculateActionScore(const FString& ActionName) const
{
	// 예시: 단순 랜덤 + 상황 기반 가중치로 확장 가능
	if (ActionName == "Eat")  return FMath::FRandRange(0.2f, 0.8f);
	if (ActionName == "Flee") return FMath::FRandRange(0.5f, 1.0f);
	return 0.0f;
}

void ADory::ExcuteAction(const FString& ActionName)
{
	// 진짜 실행은 BT Task 쪽에서 하는 것이 원칙이지만,
	// 필요 시 여기서도 공용 로직을 호출할 수 있음.
	if (ActionName == "Eat")
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Dory::ExecuteAction Eat"));
	}
	else if (ActionName == "Flee")
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Dory::ExecuteAction Flee"));
	}
}

void ADory::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

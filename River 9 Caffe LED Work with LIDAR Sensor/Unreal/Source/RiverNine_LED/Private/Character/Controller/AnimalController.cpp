// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Controller/AnimalController.h"
#include "Component/UtilityComponent.h"

// Engine
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAnimalController::AAnimalController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnimalController::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimalController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAnimalController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (InPawn)
	{
		SetupBehaviorAndBlackboard();
	}
}

void AAnimalController::SetupBehaviorAndBlackboard()
{
	if (AnimalTree)
	{
		// BlacboardComponent는 UseBlackboard 함수가 실행될 때, 자동 생성.
		UBlackboardComponent* BlackboardComp = nullptr;
		if (UseBlackboard(AnimalTree->BlackboardAsset, BlackboardComp))
		{
			AnimalBlackBoard = BlackboardComp;

			// Pawn의 유틸리티 컴포넌트에 블랙보드 주입
			if (APawn* P = GetPawn())
			{
				if (UUtilityComponent* Util = P->FindComponentByClass<UUtilityComponent>())
				{
					Util->BlackboardComp = AnimalBlackBoard;
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AnimalController: Blackboard Component is set."));
				}
			}

			RunBehaviorTree(AnimalTree);
		}
	}
}

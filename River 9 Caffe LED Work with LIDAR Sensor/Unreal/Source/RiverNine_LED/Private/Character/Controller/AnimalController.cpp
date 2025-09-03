// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Controller/AnimalController.h"
#include "Character/Animals/AnimalBase.h"
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

			//// Pawn의 유틸리티 컴포넌트에 블랙보드 주입
			//if (AAnimalBase* Animal = Cast<AAnimalBase>(GetPawn()))
			//{
			//	Animal->GetUtilityManager()->BlackboardComp = AnimalBlackBoard;
			//}

			RunBehaviorTree(AnimalTree);
		}
	}

	//if (AnimalTree)
	//{
	//	// Controller별 BlackboardComponent 새로 생성
	//	AnimalBlackBoard = NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	//	AnimalBlackBoard->InitializeBlackboard(*AnimalTree->BlackboardAsset);

	//	// Behavior Tree 실행
	//	RunBehaviorTree(AnimalTree);

	//	// Pawn의 UtilityComponent에 블랙보드 연결
	//	if (AAnimalBase* Animal = Cast<AAnimalBase>(GetPawn()))
	//	{
	//		if (Animal->GetUtilityManager())
	//		{
	//			Animal->GetUtilityManager()->BlackboardComp = AnimalBlackBoard;
	//		}
	//	}
	//}
}

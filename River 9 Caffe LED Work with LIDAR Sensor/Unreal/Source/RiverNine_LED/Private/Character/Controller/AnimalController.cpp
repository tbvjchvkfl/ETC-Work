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
		// BlacboardComponent�� UseBlackboard �Լ��� ����� ��, �ڵ� ����.
		UBlackboardComponent* BlackboardComp = nullptr;
		if (UseBlackboard(AnimalTree->BlackboardAsset, BlackboardComp))
		{
			AnimalBlackBoard = BlackboardComp;

			//// Pawn�� ��ƿ��Ƽ ������Ʈ�� ������ ����
			//if (AAnimalBase* Animal = Cast<AAnimalBase>(GetPawn()))
			//{
			//	Animal->GetUtilityManager()->BlackboardComp = AnimalBlackBoard;
			//}

			RunBehaviorTree(AnimalTree);
		}
	}

	//if (AnimalTree)
	//{
	//	// Controller�� BlackboardComponent ���� ����
	//	AnimalBlackBoard = NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	//	AnimalBlackBoard->InitializeBlackboard(*AnimalTree->BlackboardAsset);

	//	// Behavior Tree ����
	//	RunBehaviorTree(AnimalTree);

	//	// Pawn�� UtilityComponent�� ������ ����
	//	if (AAnimalBase* Animal = Cast<AAnimalBase>(GetPawn()))
	//	{
	//		if (Animal->GetUtilityManager())
	//		{
	//			Animal->GetUtilityManager()->BlackboardComp = AnimalBlackBoard;
	//		}
	//	}
	//}
}

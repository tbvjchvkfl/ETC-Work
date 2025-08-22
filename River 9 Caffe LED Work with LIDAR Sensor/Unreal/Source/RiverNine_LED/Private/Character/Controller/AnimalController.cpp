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
		// BlacboardComponent�� UseBlackboard �Լ��� ����� ��, �ڵ� ����.
		UBlackboardComponent* BlackboardComp = nullptr;
		if (UseBlackboard(AnimalTree->BlackboardAsset, BlackboardComp))
		{
			AnimalBlackBoard = BlackboardComp;

			// Pawn�� ��ƿ��Ƽ ������Ʈ�� ������ ����
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

// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Component/UtilityComponent.h"
#include "Character/Controller/AnimalController.h"
#include "Character/Utility/UtilityActions.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UUtilityComponent::UUtilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	AvailableActions.Empty();
	BlackboardComp = nullptr;
}

void UUtilityComponent::BeginPlay()
{
	Super::BeginPlay();
	UUtilityMoveAction* MoveAction = NewObject<UUtilityMoveAction>(this);
	MoveAction->InitMoveAction();
	AvailableActions.Add(MoveAction);

	UUtilityFleeAction* FleeAction = NewObject<UUtilityFleeAction>(this);
	FleeAction->InitFleeAction();
	AvailableActions.Add(FleeAction);
}

void UUtilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

UUtilityActionBase* UUtilityComponent::EvaluateBestAction()
{
	UUtilityActionBase* BestAction = nullptr;
	float BestScore = -FLT_MAX;

	for (UUtilityActionBase* const &Action : AvailableActions)
	{
		float Score = 0.0f;
		Score = Action->CalculateActionScore();

		if (Score > BestScore)
		{
			BestScore = Score;
			BestAction = Action;
		}
	}

	if (BlackboardComp && BestAction)
	{
		BlackboardComp->SetValueAsName("Selected Action Name", BestAction->ActionName);
		BlackboardComp->SetValueAsObject("Selected Action", BestAction);
	}
	return BestAction;
}

void UUtilityComponent::ForceExecuteAction(UUtilityActionBase* ActionBase)
{
	if (ActionBase)
	{
		BlackboardComp->SetValueAsBool("Check Interaction", true);
		BlackboardComp->SetValueAsName("Selected Action Name", ActionBase->ActionName);
		BlackboardComp->SetValueAsObject("Selected Action", ActionBase);
	}
}

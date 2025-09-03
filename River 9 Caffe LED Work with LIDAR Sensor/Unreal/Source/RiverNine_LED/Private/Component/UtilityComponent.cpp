// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Component/UtilityComponent.h"
#include "Character/Animals/AnimalBase.h"
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

	Owner = Cast<AAnimalBase>(GetOwner());
	if (Owner)
	{
		AvailableActions.Add(NewObject<UUtilityMoveAction>(Owner));
		AvailableActions.Add(NewObject<UUtilityFleeAction>(Owner));
		AvailableActions.Add(NewObject<UUtilityHideAction>(Owner));

		for (auto& Action : AvailableActions)
		{
			Action->InitAction(Owner);
		}

		if (AAnimalController* AnimalCont = Cast<AAnimalController>(Owner->GetController()))
		{
			BlackboardComp = AnimalCont->AnimalBlackBoard;
		}
	}
}

void UUtilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FName UUtilityComponent::EvaluateBestAction()
{
	FName BestAction;
	float BestScore = -FLT_MAX;
	
	for (UUtilityActionBase* const &Action : AvailableActions)
	{
		float Score = 0.0f;
		Score = Action->CalculateActionScore();
	
		if (Score > BestScore)
		{
			BestScore = Score;
			BestAction = Action->ActionName;
		}
	}
	
	if (BlackboardComp && !BestAction.IsNone())
	{
		BlackboardComp->SetValueAsName("Selected Action Name", BestAction);
	}
	return BestAction;
}

void UUtilityComponent::ForceExecuteAction(UUtilityActionBase* ActionBase)
{
	if (ActionBase)
	{
		BlackboardComp->SetValueAsBool("Check Interaction", true);
		BlackboardComp->SetValueAsName("Selected Action Name", ActionBase->ActionName);
	}
}

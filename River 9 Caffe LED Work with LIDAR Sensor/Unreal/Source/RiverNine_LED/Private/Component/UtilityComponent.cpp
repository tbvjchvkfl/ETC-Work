// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Component/UtilityComponent.h"
#include "Character/Controller/AnimalController.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UUtilityComponent::UUtilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	AvailableActions.Empty();
	BlackboardComp = nullptr;
	SelectedActionKey = FName("SelectedAction");
}

void UUtilityComponent::BeginPlay()
{
	Super::BeginPlay();
	AvailableActions.Add(NewObject<UUtilityMoveAction>(this));
	AvailableActions.Add(NewObject<UUtilityFleeAction>(this));
}

void UUtilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUtilityComponent::EvaluateBestAction()
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

	//if (BlackboardComp && BestActionName != NAME_None)
	//{
	//	BlackboardComp->SetValueAsName(SelectedActionKey, BestActionName);
	//}
}
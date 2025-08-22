// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Component/UtilityComponent.h"
#include "Character/Controller/AnimalController.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UUtilityComponent::UUtilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	ActionList.Empty();
	BlackboardComp = nullptr;
	SelectedActionKey = FName("SelectedAction");
}

void UUtilityComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UUtilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	EvaluateBestAction();
}

void UUtilityComponent::EvaluateBestAction()
{
	if (!BlackboardComp || ActionList.Num() == 0) return;

	float MaxScore = -FLT_MAX;
	FString BestActionStr;

	if (ActionList.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No actions available in UtilityComponent."));
	}
	else
	{
		for (auto& Action : ActionList)
		{
			if (!Action.ActionInterface)
			{
				continue;
			}
			else
			{
				const float Score = Action.ActionInterface->CalculateActionScore(Action.ActionName);
				const float FinalScore = Score + Action.BaseScore;

				if (FinalScore > MaxScore)
				{
					MaxScore = FinalScore;
					BestActionStr = Action.ActionName;
				}
			}
		}
	}

	// Blackboard(Name)으로 기록
	if (!BestActionStr.IsEmpty())
	{
		BlackboardComp->SetValueAsName(SelectedActionKey, FName(*BestActionStr));
	}
}
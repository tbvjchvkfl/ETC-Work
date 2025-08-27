// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/BT/T_ExecuteAction.h"
#include "Character/Controller/AnimalController.h"
#include "Character/Utility/UtilityActionBase.h"
#include "Character/Animals/AnimalBase.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UT_ExecuteAction::UT_ExecuteAction()
{
	NodeName = TEXT("Execute Action");
	bNotifyTick = true;
}

EBTNodeResult::Type UT_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ActionName == OwnerComp.GetBlackboardComponent()->GetValueAsName("Selected Action Name"))
	{
		Action = Cast<UUtilityActionBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Selected Action"));
		if (Action)
		{
			Action->SetTargetLocation();
		}
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UT_ExecuteAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool("Check Interaction"))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("Check Interaction", false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	if (Action)
	{
		Action->ExecuteAction();

		if (Action->CompleteAction())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/BT/T_ExecuteAction.h"
#include "Character/Controller/AnimalController.h"
#include "Character/Utility/UtilityActionBase.h"
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UT_ExecuteAction::UT_ExecuteAction()
{
	NodeName = TEXT("Execute Action");
	bNotifyTick = true;
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UT_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Owner = Cast<AAnimalBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (Owner)
	{
		OwningUtilityManager = Owner->GetUtilityManager();
		if (OwningUtilityManager)
		{
			for (auto& Action : OwningUtilityManager->AvailableActions)
			{
				if (Action->ActionName == OwningUtilityManager->BlackboardComp->GetValueAsName("Selected Action Name"))
				{
					CurrentAction = Action;
					CurrentAction->SetTargetLocation();
					break;
				}
			}
		}
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Succeeded;
}

void UT_ExecuteAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (Owner && CurrentAction)
	{
		if (CurrentAction->ActionName != "Flee Action" && OwningUtilityManager->BlackboardComp->GetValueAsBool("Check Interaction"))
		{
			OwningUtilityManager->BlackboardComp->SetValueAsBool("Check Interaction", false);
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Changed Action"));
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		if (Owner->CheckObstacleTargetLocation())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}

		CurrentAction->ExecuteAction();

		if (CurrentAction->CompleteAction())
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}

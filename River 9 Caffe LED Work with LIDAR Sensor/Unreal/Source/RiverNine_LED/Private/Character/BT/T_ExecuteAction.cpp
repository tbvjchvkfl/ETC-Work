// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/BT/T_ExecuteAction.h"
#include "Character/Controller/AnimalController.h"

// Engine
#include "BehaviorTree/BlackboardComponent.h"

UT_ExecuteAction::UT_ExecuteAction()
{
	NodeName = TEXT("Execute Action");
}

EBTNodeResult::Type UT_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Failed;
}

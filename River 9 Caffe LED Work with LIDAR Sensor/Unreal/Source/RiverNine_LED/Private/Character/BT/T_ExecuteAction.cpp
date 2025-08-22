// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BT/T_ExecuteAction.h"

UT_ExecuteAction::UT_ExecuteAction()
{
	NodeName = TEXT("Execute Action");
}

EBTNodeResult::Type UT_ExecuteAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

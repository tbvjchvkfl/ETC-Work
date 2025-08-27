// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "T_ExecuteAction.generated.h"

class UUtilityActionBase;
class AAnimalBase;

UCLASS()
class RIVERNINE_LED_API UT_ExecuteAction : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere)
	FName ActionName;

	UPROPERTY(VisibleAnywhere)
	UUtilityActionBase* Action = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	AAnimalBase* Owner;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	UT_ExecuteAction();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

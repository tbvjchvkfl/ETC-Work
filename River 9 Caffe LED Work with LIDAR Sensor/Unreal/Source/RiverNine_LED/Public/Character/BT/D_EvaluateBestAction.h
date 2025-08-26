// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "D_EvaluateBestAction.generated.h"

/**
 * 
 */
UCLASS()
class RIVERNINE_LED_API UD_EvaluateBestAction : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	UD_EvaluateBestAction();

protected:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};

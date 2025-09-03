// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/Interface/UtilityInterface.h"
#include "UtilityActionBase.generated.h"


class AAnimalBase;

UCLASS(Abstract)
class RIVERNINE_LED_API UUtilityActionBase : public UObject, public IUtilityInterface
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY()
	FName ActionName;

	

	UPROPERTY()
	float BaseScore;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void InitAction(AAnimalBase* owner) override{}
	virtual void SetTargetLocation() override {}
	virtual float CalculateActionScore() override { return 0.f; }
	virtual void ExecuteAction() override {}
	virtual bool CompleteAction() override { return false; }
};

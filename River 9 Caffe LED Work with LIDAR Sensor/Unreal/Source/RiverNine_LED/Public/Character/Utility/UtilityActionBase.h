// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Character/Interface/UtilityInterface.h"
#include "UtilityActionBase.generated.h"




UCLASS(Abstract)
class RIVERNINE_LED_API UUtilityActionBase : public UObject, public IUtilityInterface
{
	GENERATED_BODY()

public:
	virtual float CalculateActionScore() override { return 0.f; }
	virtual void ExecuteAction() override {}
};

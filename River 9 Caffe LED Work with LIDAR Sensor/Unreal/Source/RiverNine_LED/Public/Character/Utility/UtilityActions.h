// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Utility/UtilityActionBase.h"
#include "UtilityActions.generated.h"

class AAnimalBase;
class UFloatingPawnMovement;

UCLASS()
class RIVERNINE_LED_API UUtilityMoveAction : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY()
	AAnimalBase* Owner;

	UPROPERTY()
	UFloatingPawnMovement* MoveComp;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	void InitMoveAction();
	virtual void SetTargetLocation() override;
	virtual bool CompleteAction() override;
	virtual float CalculateActionScore() override;
	virtual void ExecuteAction() override;
};

UCLASS()
class RIVERNINE_LED_API UUtilityFleeAction : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY()
	AAnimalBase* Owner;

	UPROPERTY()
	UFloatingPawnMovement* MoveComp;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	void InitFleeAction();
	virtual void SetTargetLocation() override;
	virtual bool CompleteAction() override;
	virtual float CalculateActionScore() override;
	virtual void ExecuteAction() override;
};

UCLASS()
class RIVERNINE_LED_API UUtilityActions : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UUtilityMoveAction* MoveAction;

	UPROPERTY()
	UUtilityFleeAction* FleeAction;
};

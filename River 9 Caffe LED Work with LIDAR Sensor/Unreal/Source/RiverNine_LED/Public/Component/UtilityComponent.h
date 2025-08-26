// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Utility/UtilityActionBase.h"
#include "UtilityComponent.generated.h"

class UBlackboardComponent;

UCLASS()
class RIVERNINE_LED_API UUtilityMoveAction : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	virtual float CalculateActionScore() override
	{
		return 0.0f;
	}

	virtual void ExecuteAction() override
	{

	}
};

UCLASS()
class RIVERNINE_LED_API UUtilityFleeAction : public UUtilityActionBase
{
	GENERATED_BODY()

public:
	virtual float CalculateActionScore() override
	{
		return 0.0f;
	}

	virtual void ExecuteAction() override
	{

	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIVERNINE_LED_API UUtilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property|Utility")
	TArray<UUtilityActionBase*> AvailableActions;

	UPROPERTY(VisibleAnywhere, Category = "Property|Utility")
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditAnywhere, Category = "Property|Utility")
	FName SelectedActionKey;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	UUtilityComponent();
	void EvaluateBestAction();
private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

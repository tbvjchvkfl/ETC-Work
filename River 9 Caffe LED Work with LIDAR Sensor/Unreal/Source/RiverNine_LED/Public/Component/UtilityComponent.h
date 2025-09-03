// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UtilityComponent.generated.h"

class UBlackboardComponent;
class UUtilityActionBase;
class AAnimalBase;

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

	UPROPERTY(VisibleAnywhere, Category = "Property|Utility")
	AAnimalBase* Owner;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	UUtilityComponent();
	//UUtilityActionBase* EvaluateBestAction();
	FName EvaluateBestAction();
	void ForceExecuteAction(UUtilityActionBase* ActionBase);
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

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UtilityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUtilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RIVERNINE_LED_API IUtilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void InitAction(class AAnimalBase* owner) = 0;
	virtual void SetTargetLocation() = 0;
	virtual float CalculateActionScore() = 0;
	virtual void ExecuteAction() = 0;
	virtual bool CompleteAction() = 0;
	
	/*UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility")
	float CalculateActionScore(const FName& ActionName) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Utility")
	void ExecuteAction(const FName& ActionName);*/
};

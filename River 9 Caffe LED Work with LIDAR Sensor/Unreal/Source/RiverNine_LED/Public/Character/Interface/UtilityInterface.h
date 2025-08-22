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
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual float CalculateActionScore(const FString& ActionName) const = 0;
	virtual void ExcuteAction(const FString& ActionName) = 0;
};

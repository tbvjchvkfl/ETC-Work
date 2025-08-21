// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RNLED_ModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RIVERNINE_LED_API ARNLED_ModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================



	//==============================================================
	//=                          Function                          =
	//==============================================================
	ARNLED_ModeBase();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};

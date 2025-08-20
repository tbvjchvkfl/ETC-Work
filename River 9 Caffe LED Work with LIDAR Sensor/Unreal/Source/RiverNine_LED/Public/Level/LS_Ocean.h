// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LS_Ocean.generated.h"

class APlayerCharacterController;

UCLASS()
class RIVERNINE_LED_API ALS_Ocean : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	ALS_Ocean();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	APlayerCharacterController* PCController;


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void MouseInteraction();
};

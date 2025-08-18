// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ObjectBase.generated.h"

UCLASS()
class RIVERNINE_LED_API AObjectBase : public ACharacter
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================



	//==============================================================
	//=                          Function                          =
	//==============================================================
	AObjectBase();

protected:
	//==============================================================
	//=                          Variable                          =
	//==============================================================



	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

USTRUCT()
struct FPlayerSaveInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FVector PlayerLocation;

	UPROPERTY()
	FRotator PlayerRotation;
};

UCLASS()
class RIVERNINE_LED_API USaveData : public USaveGame
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere)
	FPlayerSaveInfo PlayerSaveInfo;

	
	//==============================================================
	//=                          Function                          =
	//==============================================================
};

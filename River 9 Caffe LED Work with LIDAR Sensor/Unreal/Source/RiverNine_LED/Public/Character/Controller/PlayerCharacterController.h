// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class USaveGame;

UCLASS()
class RIVERNINE_LED_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()
public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Controller | Save")
	TSubclassOf<USaveGame> SaveGameClass;

	UPROPERTY(EditDefaultsOnly, Category = "Controller | Value")
	float LookingRotationValue;

	UPROPERTY(VisibleAnywhere, Category = "Controller | Value")
	bool bIsEnabledTurn;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	APlayerCharacterController();
	void Load();

private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Controller | Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditDefaultsOnly, Category = "Controller | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Controller | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Controller | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* SaveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Controller | Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* TestAction;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Save();
	void EnabledTurnOnGoing();
	void EnabledTurnComplete();
};

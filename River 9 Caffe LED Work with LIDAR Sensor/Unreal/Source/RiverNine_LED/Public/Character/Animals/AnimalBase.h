// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AnimalBase.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UFloatingPawnMovement;
class UUtilityComponent;
class AMovementLimitVolume;

UCLASS()
class RIVERNINE_LED_API AAnimalBase : public APawn
{
	GENERATED_BODY()

public:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY()
	bool bIsInteraction;

	UPROPERTY(EditAnywhere, Category = "Property | Value")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Property | Value")
	float FleeSpeed;
	
	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	int InteractionCount = 0;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	AAnimalBase();
	FORCEINLINE UFloatingPawnMovement* GetFloatingMovementComponent()const { return MovementComponent; }
	FORCEINLINE UUtilityComponent* GetUtilityManager()const { return UtilityManager; }
	FORCEINLINE AMovementLimitVolume* GetMovementLimitVolume() const { return MovementLimitVolume; }

	void TriggerFleeAction();
	FVector SetHideLocation();
protected:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PawnMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UUtilityComponent* UtilityManager;

	UPROPERTY(EditAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	AMovementLimitVolume* MovementLimitVolume;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

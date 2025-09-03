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

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	int InteractionCount = 0;


	// 일반 이동

	UPROPERTY(EditAnywhere, Category = "Property | Value")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Property | Value")
	float FleeSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	FVector TargetLocation;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	FVector CurrentVelocity;

	// 가속도
	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	float MoveAcceleration = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	float Deceleration = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	float MaxMoveSpeed = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	float FleeAcceleration = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Property | Value")
	float MaxFleeSpeed = 800.0f;
	//==============================================================
	//=                          Function                          =
	//==============================================================
	AAnimalBase();
	FORCEINLINE UFloatingPawnMovement* GetFloatingMovementComponent()const { return MovementComponent; }
	FORCEINLINE UUtilityComponent* GetUtilityManager()const { return UtilityManager; }
	FORCEINLINE AMovementLimitVolume* GetMovementLimitVolume() const { return MovementLimitVolume; }
	FORCEINLINE USkeletalMeshComponent* GetPawnMesh()const { return PawnMesh; }

	void TriggerFleeAction();
	FVector SetHideLocation();
	bool CheckObstacleTargetLocation();
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

	UPROPERTY(VisibleAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	AMovementLimitVolume* MovementLimitVolume;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
};

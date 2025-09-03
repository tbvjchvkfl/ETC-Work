// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HideObject.generated.h"

class USphereComponent;

UCLASS()
class RIVERNINE_LED_API AHideObject : public AActor
{
	GENERATED_BODY()
	
public:	
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	AHideObject();



private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(VisibleAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere, Category = "Property | Component", meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereColiision;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};

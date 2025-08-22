// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/Interface/UtilityInterface.h"
#include "UtilityComponent.generated.h"

class UBlackboardComponent;

USTRUCT()
struct FUtilityAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString ActionName;

	UPROPERTY(EditAnywhere)
	float BaseScore;

	UPROPERTY(EditAnywhere)
	TScriptInterface<IUtilityInterface> ActionInterface;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIVERNINE_LED_API UUtilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//==============================================================
	//=                          Variable                          =
	//==============================================================
	UPROPERTY(EditAnywhere, Category = "Property|Utility")
	TArray<FUtilityAction> ActionList;

	// ���̺긮�� ������ ���� �߰�
	UPROPERTY(VisibleAnywhere, Category = "Property|Utility")
	UBlackboardComponent* BlackboardComp;

	// Blackboard�� ����� Key (Name Ÿ�� ����)
	UPROPERTY(EditAnywhere, Category = "Property|Utility")
	FName SelectedActionKey;

	//==============================================================
	//=                          Function                          =
	//==============================================================
	UUtilityComponent();
	// ��ƿ��Ƽ �� (BT ����/ƽ ��� ȣ��)
	void EvaluateBestAction();
private:
	//==============================================================
	//=                          Variable                          =
	//==============================================================


	//==============================================================
	//=                          Function                          =
	//==============================================================
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

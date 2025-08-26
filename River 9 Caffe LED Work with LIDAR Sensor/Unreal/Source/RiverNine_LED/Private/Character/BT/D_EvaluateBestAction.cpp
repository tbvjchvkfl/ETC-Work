// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/BT/D_EvaluateBestAction.h"
#include "Character/Controller/AnimalController.h"
#include "Character/Animals/AnimalBase.h"
#include "Component/UtilityComponent.h"

// Engine
#include "Behaviortree/BlackboardComponent.h"

UD_EvaluateBestAction::UD_EvaluateBestAction()
{
	NodeName = TEXT("EvaluateBestAction");
}

bool UD_EvaluateBestAction::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool ReturnValue = false;
    if (AAnimalBase* FishCharacter = Cast<AAnimalBase>(OwnerComp.GetAIOwner()->GetPawn()))
    {
        FishCharacter->GetUtilityManager()->EvaluateBestAction();
        ReturnValue = true;
    }
    /*if (AAnimalController* AI = Cast<AAnimalController>(OwnerComp.GetAIOwner()))
    {
        if (UUtilityComponent* UtilityComp = AI->GetPawn()->FindComponentByClass<UUtilityComponent>())
        {
            FName BestAction = UtilityComp->EvaluateBestAction();
            if (BestAction != NAME_None)
            {
                ReturnValue = true;
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("UtilityComponent is Null"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("False"));
    }*/
    return ReturnValue;
}

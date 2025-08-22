// Fill out your copyright notice in the Description page of Project Settings.


// Framework
#include "Character/Controller/PlayerCharacterController.h"
#include "Data/SaveData.h"

// Engine
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacterController::APlayerCharacterController()
{
	PrimaryActorTick.bCanEverTick = true;
	LookingRotationValue = 1.0f;
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* const SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultContext)
		{
			SubSystem->AddMappingContext(DefaultContext, 0);
		}
	}
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* const EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Look);
		EnhancedInputComponent->BindAction(SaveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Save);
	}
}

void APlayerCharacterController::Move(const FInputActionValue& Value)
{
	FVector MovementVector = Value.Get<FVector>();
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Green, FString::Printf(TEXT("MovementVector : %f, %f, %f"), MovementVector.X, MovementVector.Y, MovementVector.Z));
	const FRotator YawRotation(0, GetControlRotation().Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector UpDirection = FVector::UpVector;

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
	GetPawn()->AddMovementInput(UpDirection, MovementVector.Z);
}

void APlayerCharacterController::Look(const FInputActionValue& Value)
{
	const FVector2D LookDirection = Value.Get<FVector2D>();
	
	AddYawInput(LookDirection.X * LookingRotationValue * GetWorld()->GetDeltaSeconds());
	AddPitchInput(LookDirection.Y * LookingRotationValue * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacterController::Save()
{
	if (GetPawn())
	{
		if (USaveData* SaveDataInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(SaveGameClass)))
		{
			SaveDataInstance->PlayerSaveInfo.PlayerLocation = GetPawn()->GetActorLocation();
			SaveDataInstance->PlayerSaveInfo.PlayerRotation = GetPawn()->GetActorRotation();

			UGameplayStatics::SaveGameToSlot(SaveDataInstance, TEXT("PlayerSaveSlot"), 0);
		}
	}
}

void APlayerCharacterController::Load()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("PlayerSaveSlot"), 0))
	{
		if (USaveData* SaveDataInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("PlayerSaveSlot"), 0)))
		{
			if (GetPawn())
			{
				SetControlRotation(SaveDataInstance->PlayerSaveInfo.PlayerRotation);
				GetPawn()->SetActorLocation(SaveDataInstance->PlayerSaveInfo.PlayerLocation);
				GetPawn()->SetActorRotation(SaveDataInstance->PlayerSaveInfo.PlayerRotation);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Load Fail!!!"));
		return;
	}
}
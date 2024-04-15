// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/KDT2PlayerController.h"
#include "Data/Input/BasicInputDataConfig.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Actors/CameraManager/KDT2PlayerCameraManager.h"

AKDT2PlayerController::AKDT2PlayerController()
{
	PlayerCameraManagerClass = AKDT2PlayerCameraManager::StaticClass();
}

void AKDT2PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AKDT2PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(BasicInputDataConfig->InputMappingContext, 0);
}

void AKDT2PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* BasicInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(BasicInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
}

void AKDT2PlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0., Rotation.Yaw, 0.);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
}

void AKDT2PlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

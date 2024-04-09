// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/KDT2FloatingPawnMovement.h"

float GetAxisDeltaRotation(float InAxisRotationRate, float DeltaTime)
{
	// Values over 360 don't do anything, see FMath::FixedTurn. However we are trying to avoid giant floats from overflowing other calculations.
	return (InAxisRotationRate >= 0.f) ? FMath::Min(InAxisRotationRate * DeltaTime, 360.f) : 360.f;
}

void UKDT2FloatingPawnMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
	CurrentRotation.DiagnosticCheckNaN(TEXT("UKDT2FloatingPawnMovement::TickComponent():CurrentRotation"));


}

FRotator UKDT2FloatingPawnMovement::GetDeltaRotation(float DeltaTime) const
{
	return FRotator(GetAxisDeltaRotation(RotationRate.Pitch, DeltaTime), GetAxisDeltaRotation(RotationRate.Yaw, DeltaTime), GetAxisDeltaRotation(RotationRate.Roll, DeltaTime));
}
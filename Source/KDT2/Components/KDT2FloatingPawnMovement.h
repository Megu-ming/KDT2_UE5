// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "KDT2FloatingPawnMovement.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = Movement, meta = (BlueprintSpawnableComponent))
class KDT2_API UKDT2FloatingPawnMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FRotator GetDeltaRotation(float DeltaTime) const;

private:
	FRotator RotationRate = FRotator(0., 360., 0.);
};

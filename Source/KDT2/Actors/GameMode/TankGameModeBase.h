// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GameMode/KDT2GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KDT2_API ATankGameModeBase : public AKDT2GameModeBase
{
	GENERATED_BODY()
	
public:
	ATankGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	FActorPool& GetProjectilePool() { return ProjectilePool; }

protected:
	FActorPool ProjectilePool;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Sun.generated.h"

UCLASS()
class KDT2_API ASun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASun();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnSunPower(float InPower);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshSunComponent = nullptr;

	UPROPERTY(EditAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshEarthComponent = nullptr;

	UPROPERTY()
	UTimelineComponent* SunPowerTimelineComponent = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;

	UPROPERTY(Category="Speed",EditAnywhere)
	double EarthRotationSpeed = 20.0;
	UPROPERTY(Category="Speed", EditAnywhere)
	double SceneRotationSpeed = 80.0;

	static inline UMaterial* SunMaterial = nullptr;
	static inline UMaterial* EarthMaterial = nullptr;
};

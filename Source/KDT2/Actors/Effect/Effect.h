// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Effect.generated.h"

USTRUCT()
struct KDT2_API FEffectDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<USoundBase>> Audio;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> Particle;
};

UCLASS()
class KDT2_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();

	void SetEffectData(const FEffectDataTableRow* InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystemComponent* Particle;
};

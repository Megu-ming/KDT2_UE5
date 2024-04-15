// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Effect/Effect.h"

// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SetRootComponent(AudioComponent);
	Particle->SetupAttachment(AudioComponent);
}

void AEffect::SetEffectData(const FEffectDataTableRow* InData)
{
	ensure(InData);
	const int32 AudioCount = InData->Audio.Num();
	if (AudioCount > 1)
	{
		const int32 RandomIndex = FMath::RandRange(0, AudioCount - 1);
		AudioComponent->Sound = InData->Audio[RandomIndex];
	}

	if (InData->Particle)
	{
		Particle->SetTemplate(InData->Particle);
	}
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


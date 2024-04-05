// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Coin/Coin.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorHelp.EditorHelp'"));
	check(Asset.Succeeded());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(Asset.Object);
}

void ACoin::Active()
{
	ITriggerInterface::Active();
}

void ACoin::InActive()
{
	ITriggerInterface::InActive();
}

void ACoin::InTrigger()
{
	ITriggerInterface::InTrigger();
}

void ACoin::OutTrigger()
{
	ITriggerInterface::OutTrigger();
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


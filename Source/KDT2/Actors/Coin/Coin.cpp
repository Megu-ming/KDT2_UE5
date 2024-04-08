// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Coin/Coin.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Asset{TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorHelp.EditorHelp'")};
	check(Asset.Succeeded());

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetStaticMesh(Asset.Object);
}

void ACoin::Active()
{
	ITriggerInterface::Active();
}

void ACoin::Inactive()
{
	ITriggerInterface::Inactive();
}

void ACoin::InTrigger()
{
	ITriggerInterface::InTrigger();
}

void ACoin::OutTrigger()
{
	ITriggerInterface::OutTrigger();
}

void ACoin::OnSubData(const FDataTableRowHandle& InSubData)
{
	ITriggerInterface::OnSubData(InSubData);
	const FCoinDataTableRow* Data = InSubData.GetRow<FCoinDataTableRow>(TEXT(""));
	if (!Data) { ensure(false); return; }

	CoinDataTableRowHandle = InSubData;
	StaticMeshComponent->SetStaticMesh(Data->StaicMesh);
	StaticMeshComponent->SetRelativeTransform(Data->StaticMeshTransform);
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


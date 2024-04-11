// Fill out your copyright notice in the Description page of Project Settings.


#include "MISC/ActorPool.h"

FActorPool::FActorPool()
{
}

FActorPool::~FActorPool()
{
	Destroy();
}

void FActorPool::Create(UWorld* World, TSubclassOf<AActor> Class, uint32 Count)
{
	if (!Pool.IsEmpty())
	{
		check(false);
		return;
	}
	FTransform DefaultTransform;
	Pool.Reserve(Count);
	ActiveActors.Reserve(Count);
	for (uint32 i = 0; i < Count; ++i)
	{
		AActor* SpawnActor = World->SpawnActorDeferred<AActor>(Class, DefaultTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		SpawnActor->SetActorEnableCollision(false);
		SpawnActor->SetActorHiddenInGame(true);
		SpawnActor->FinishSpawning(DefaultTransform, true);
		Pool.Add(SpawnActor);
	}
}

void FActorPool::Destroy()
{
	for (auto* It : Pool)
	{
		It->Destroy();
	}
	Pool.Empty();
}

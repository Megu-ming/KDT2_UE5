// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FActorPool
{
	FActorPool();
	~FActorPool();

	void Create(UWorld* World, TSubclassOf<AActor> Class, uint32 Count);
	void Destroy();

	template<class T>
	T* New(const FTransform& InTransform,bool bEnableCollision = true, AActor* Owner = nullptr, APawn* Instigator = nullptr)
	{
		AActor* Actor = nullptr;
		if (Pool.Num() == 0)
		{

			Actor = ActiveActors[0];
			ActiveActors.RemoveAt(0);
		}
		else
		{
			Actor = Pool.Pop(false);
		}
		Actor->SetOwner(Owner);
		Actor->SetInstigator(Instigator);

		Actor->SetActorEnableCollision(bEnableCollision);
		Actor->SetActorHiddenInGame(false);
		Actor->SetActorTransform(InTransform, false, nullptr, ETeleportType::TeleportPhysics);


		ActiveActors.Push(Actor);

		T* ActorT = Cast<T>(Actor);
		ensure(ActorT);

		return ActorT;
	}

	void Delete(AActor* InActor)
	{
		int32 Index = ActiveActors.Find(InActor);
		if (Index == INDEX_NONE)
		{
			check(false);
		}
		ActiveActors.RemoveAt(Index);
		Pool.Add(InActor);
	}

	TArray<AActor*> Pool;
	TArray<AActor*> ActiveActors; // Pool에서 꺼내서 외부에서 처리되고있는 Actor
};

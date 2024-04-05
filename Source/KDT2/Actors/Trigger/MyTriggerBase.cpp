// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Trigger/MyTriggerBase.h"

// Sets default values
AMyTriggerBase::AMyTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;

	ActiveRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ActiveRadius"));
	Trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	TriggerObject = CreateDefaultSubobject<UChildActorComponent>(TEXT("TriggerObject"));
	SetRootComponent(ActiveRadius);

	Trigger->SetupAttachment(GetRootComponent());
	TriggerObject->SetupAttachment(GetRootComponent());

	ActiveRadius->SetSphereRadius(600.f);
	Trigger->SetSphereRadius(120.f);

	// FText	: 국가별 처리가 가능한 문자열
	// FString	: C++ String
	// FName	: 문자열 해싱(특정 타입을 정수로 변환해서 들고 있는 것)
	//				대소문자 구분x, 정수로 변환해서 관리, 검색 속도를 향상시키기 위해서 사용
	ActiveRadius->SetCollisionProfileName(FCollisionPresetNameTable::PlayerDetect);
	Trigger->SetCollisionProfileName(FCollisionPresetNameTable::PlayerDetect);

	{
		// - ActiveRadius
		//		- Trigger
		//		- TriggerObject
	}

	ActiveRadius->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnActiveRadiusBeginOverlap);
	ActiveRadius->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnActiveRadiusEndOverlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnTriggerBeginOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this,&ThisClass::OnTriggerEndOverlap);
}

void AMyTriggerBase::OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Active();
}

void AMyTriggerBase::OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InActive();
}

void AMyTriggerBase::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InTrigger();
}

void AMyTriggerBase::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OutTrigger();
}

AActor* AMyTriggerBase::GetTriggerObject()
{
	AActor* Actor= TriggerObject->GetChildActor();
	if (!IsValid(Actor))
	{
		ensureAlwaysMsgf(false,TEXT("Actor is nullptr"));
		return nullptr;
	}

	const bool bIsImplemented = Actor->GetClass()->ImplementsInterface(UTriggerInterface::StaticClass());
	if (!bIsImplemented)
	{
		ensureAlwaysMsgf(false, TEXT("Class must ImplementsInterface ITriggerInterface"));
		return nullptr;
	}

	return Actor;
}

void AMyTriggerBase::Active()
{
	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface->Active();
	}
	else
	{
		ITriggerInterface::Execute_ReceiveActive(Actor);
	}
}

void AMyTriggerBase::InActive()
{
	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface;
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInActive(Actor);
	}
}

void AMyTriggerBase::InTrigger()
{
	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface;
	}
	else
	{
		ITriggerInterface::Execute_ReceiveInTrigger(Actor);
	}
}

void AMyTriggerBase::OutTrigger()
{
	AActor* Actor = GetTriggerObject();
	if (!Actor) { return; }

	ITriggerInterface* Interface = Cast<ITriggerInterface>(Actor);
	if (Interface)
	{
		Interface;
	}
	else
	{
		ITriggerInterface::Execute_ReceiveOutTrigger(Actor);
	}
}

// Called when the game starts or when spawned
void AMyTriggerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Planet.h"

// Sets default values
APlanet::APlanet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	PlanetAxis = CreateDefaultSubobject<USceneComponent>(TEXT("PlanetAxis"));
	PlanetStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetStaticMeshComponent"));
	CloudAxis = CreateDefaultSubobject<USceneComponent>(TEXT("CloudAxis"));
	CloudStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudStaticMeshComponent"));
	SetRootComponent(DefaultSceneRoot);

	PlanetAxis->SetupAttachment(GetRootComponent());
	PlanetStaticMeshComponent->SetupAttachment(PlanetAxis);

	CloudAxis->SetupAttachment(GetRootComponent());
	CloudStaticMeshComponent->SetupAttachment(CloudAxis);
	CloudStaticMeshComponent->SetRelativeScale3D(FVector(1.01, 1.01, 1.01));
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/EditorMeshes/EditorSphere.EditorSphere'"));
		ensure(ObjectFinder.Object);
		PlanetStaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
		CloudStaticMeshComponent->SetStaticMesh(ObjectFinder.Object);
	}
}

void APlanet::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const int32 ElementIndex = 0;
	UMaterialInterface* MaterialInterface = PlanetStaticMeshComponent->GetMaterial(ElementIndex);
	PlanetMaterialInstanceDynamic = PlanetStaticMeshComponent->CreateDynamicMaterialInstance(ElementIndex, MaterialInterface);
	
	CloudStaticMeshComponent->SetVisibility(bCloud);

	const int32 NumberOfSatellite = SatelliteArray.Num();

	for (int32 i = 0; i < NumberOfSatellite; ++i)
	{
		if (!SatelliteArray[i].ChildActorComponent)
		{
			SatelliteArray[i].Axis = NewObject<USceneComponent>(this);
			SatelliteArray[i].Axis->RegisterComponent();
			SatelliteArray[i].Axis->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			SatelliteArray[i].ChildActorComponent = NewObject<UChildActorComponent>(this);
			SatelliteArray[i].ChildActorComponent->RegisterComponent();
			SatelliteArray[i].ChildActorComponent->AttachToComponent(SatelliteArray[i].Axis, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
	}
}

// Called when the game starts or when spawned
void APlanet::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlanet::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		const double DeltaSpeed = (DeltaTime * PlanetRotationSpeed);
		const FRotator Rotator{ 0.,DeltaSpeed,0. };
		const FQuat Quat = Rotator.Quaternion();
		PlanetStaticMeshComponent->AddLocalRotation(Quat);
	}
	{
		const double DeltaSpeed = (DeltaTime * CloudeRotationSpeed);
		const FRotator Rotator{ 0.,DeltaSpeed,0. };
		const FQuat Quat = Rotator.Quaternion();
		CloudStaticMeshComponent->AddLocalRotation(Quat);
	}

	for (auto& It : SatelliteArray)
	{
		const double DeltaSpeed = (DeltaTime * It.RotationSpeed);
		const FRotator Rotator{ 0.,DeltaSpeed,0. };
		const FQuat Quat = Rotator.Quaternion();
		It.Axis->AddLocalRotation(Quat);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Sun.h"

// Sets default values
ASun::ASun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bool bCDO = HasAnyFlags(EObjectFlags::RF_ClassDefaultObject);

	StaticMeshSunComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshSun"));
	StaticMeshEarthComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshEarth"));
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SunPowerTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("SunPower Timeline"));
	
	RootComponent = StaticMeshSunComponent;
	SceneComponent->SetupAttachment(StaticMeshSunComponent);
	StaticMeshEarthComponent->SetupAttachment(SceneComponent);

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
		ensure(ObjectFinder.Object);
		StaticMeshSunComponent->SetStaticMesh(ObjectFinder.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> ObjectFinder(TEXT("/Script/Engine.Material'/Game/KDT/Blueprint/SolarSystem/MT_Sun.MT_Sun'"));
		ensure(ObjectFinder.Object);
		SunMaterial = ObjectFinder.Object;
		StaticMeshSunComponent->SetMaterial(0, SunMaterial);
	}
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> ObjectFinder(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
		ensure(ObjectFinder.Object);
		StaticMeshEarthComponent->SetStaticMesh(ObjectFinder.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> ObjectFinder(TEXT("/Script/Engine.Material'/Game/KDT/Blueprint/SolarSystem/MT_Earth.MT_Earth'"));
		EarthMaterial = ObjectFinder.Object;
		StaticMeshEarthComponent->SetMaterial(0, EarthMaterial);

		StaticMeshEarthComponent->SetRelativeLocation(FVector(200.f, 0, 0));
		StaticMeshEarthComponent->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	}

	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> ObjectFinder(TEXT("/Script/Engine.CurveFloat'/Game/KDT/Blueprint/SolarSystem/Curve_SunPower.Curve_SunPower'"));
		ensure(ObjectFinder.Object);

		FOnTimelineFloat Delegate;
		Delegate.BindUFunction(this, TEXT("OnSunPower"));

		SunPowerTimelineComponent->AddInterpFloat(ObjectFinder.Object, Delegate);
		SunPowerTimelineComponent->SetPlayRate(0.5f);
		SunPowerTimelineComponent->SetLooping(true);
	}
}

void ASun::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	MID = StaticMeshSunComponent->CreateDynamicMaterialInstance(0, SunMaterial);
}

// Called when the game starts or when spawned
void ASun::BeginPlay()
{
	Super::BeginPlay();
	
	SunPowerTimelineComponent->Play();
}

// Called every frame
void ASun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SceneComponent->AddRelativeRotation(FRotator(0, SceneRotationSpeed * DeltaTime, 0));
	StaticMeshEarthComponent->AddRelativeRotation(FRotator(0, EarthRotationSpeed * DeltaTime, 0));
}

void ASun::OnSunPower(float InPower)
{
	UE_LOG(LogTemp, Warning, TEXT("Power : %f"), InPower);
	MID->SetScalarParameterValue(TEXT("Power"), InPower * 30.f);
}


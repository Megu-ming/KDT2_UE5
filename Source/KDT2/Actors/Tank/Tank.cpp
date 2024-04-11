// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/Tank.h"
#include "MISC/MISC.h"
#include "Blueprint/UserWidget.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	TurretSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("TurretSpringArm"));
	Turret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("KDT2FloatingPawnMovement"));
	
	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Player);

	CameraSpringArmComponent->bUsePawnControlRotation = true;
	CameraSpringArmComponent->bInheritRoll = false;

	TurretSpringArmComponent->bUsePawnControlRotation = true;
	TurretSpringArmComponent->bInheritRoll = false;
	TurretSpringArmComponent->bInheritPitch = false;
	TurretSpringArmComponent->bEnableCameraRotationLag = true;

	SetRootComponent(BoxComponent);
	CameraSpringArmComponent->SetupAttachment(GetRootComponent());
	DefaultCamera->SetupAttachment(CameraSpringArmComponent);
	Body->SetupAttachment(GetRootComponent());
	TurretSpringArmComponent->SetupAttachment(GetRootComponent());
	Turret->SetupAttachment(TurretSpringArmComponent);
	Muzzle->SetupAttachment(TurretSpringArmComponent);
	Arrow->SetupAttachment(Muzzle);
	ZoomCamera->SetupAttachment(Muzzle);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	ensure(UI);
	ZoomInWidget = CreateWidget<UUserWidget>(GetWorld(), UI);

	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	ProjectileRow = DataSubsystem->FindProjectile(ProjectileName);

	ProjectilePool.Create(GetWorld(), AProjectile::StaticClass(), 5);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::ZoomIn()
{
	ZoomCamera->SetActive(true);
	DefaultCamera->SetActive(false);
	ZoomInWidget->AddToViewport();
}

void ATank::ZoomOut()
{
	ZoomCamera->SetActive(false);
	DefaultCamera->SetActive(true);
	ZoomInWidget->RemoveFromParent();
}

void ATank::Fire()
{
	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer)
	{
		return;
	}
	ensure(ProjectileRow->FireDelay > 0.f);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle,ProjectileRow->FireDelay,false);
	UWorld* World = GetWorld();
	ensure(World);

	const FTransform& MuzzleTransform = Muzzle->GetComponentTransform();
	FTransform Transform = FTransform(MuzzleTransform.GetRotation(), MuzzleTransform.GetLocation());

	AProjectile* NewProjectile = ProjectilePool.New<AProjectile>(Transform, true, this, this);
	
	NewProjectile->SetProjectileData(ProjectileRow);
	NewProjectile->FinishSpawning(MuzzleTransform, true);
}
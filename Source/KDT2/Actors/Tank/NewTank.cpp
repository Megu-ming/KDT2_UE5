// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Tank/NewTank.h"
#include "Blueprint/UserWidget.h"
#include "Actors/Projectile/Projectile.h"
#include "Actors/GameMode/TankGameModeBase.h"

namespace Socket
{
	const FName FireSocket = TEXT("gun_1_jntSocket");
	const FName TurretJointSocket = TEXT("turret_jntSocket");
}

// Sets default values
ANewTank::ANewTank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	DefaultCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DefaultCamera"));
	ZoomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ZoomCamera"));
	KDT2FloatingPawnMovement = CreateDefaultSubobject<UKDT2FloatingPawnMovement>(TEXT("KDT2FloatingPawnMovement"));
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/KDT2/Blueprint/Tank/VigilanteContent/Vehicles/West_Tank_M1A1Abrams/SK_West_Tank_M1A1Abrams.SK_West_Tank_M1A1Abrams'"));
		check(Asset.Object);

		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);

		ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/KDT2/Blueprint/Tank/BPA_Tank.BPA_Tank_C'"));
		check(AnimAsset.Class);
		SkeletalMeshComponent->SetAnimClass(AnimAsset.Class);
	}

	BoxComponent->SetCollisionProfileName(FCollisionPresetNameTable::Player);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraSpringArmComponent->bUsePawnControlRotation = true;
	CameraSpringArmComponent->bInheritRoll = false;
	/*
	- BoxComponent
		- CameraSpringArmComponent
			- DefaultCamera
		- SkeletalMeshComponent
	*/
	SetRootComponent(BoxComponent);
	CameraSpringArmComponent->SetupAttachment(SkeletalMeshComponent,Socket::TurretJointSocket);
	DefaultCamera->SetupAttachment(CameraSpringArmComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	ZoomCamera->SetupAttachment(SkeletalMeshComponent, Socket::FireSocket);

	const TSet<UActorComponent*>& Components = GetComponents();
	for (auto* It : Components)
	{
		if (It != SkeletalMeshComponent)
		{
			SkeletalMeshComponent->AddTickPrerequisiteComponent(It);
		}
	}
}

void ANewTank::ZoomIn()
{
	if (!ZoomInWidget) { return; }
	ZoomCamera->SetActive(true);
	DefaultCamera->SetActive(false);
	ZoomInWidget->AddToViewport();
}

void ANewTank::ZoomOut()
{
	if (!ZoomInWidget) { return; }
	ZoomCamera->SetActive(false);
	DefaultCamera->SetActive(true);
	ZoomInWidget->RemoveFromParent();
}

void ANewTank::Fire()
{
	bool bTimer = GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle);
	if (bTimer) { return; }
	ensure(ProjectileRow->FireDelay > 0.f);
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, ProjectileRow->FireDelay, false);

	const FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(Socket::FireSocket);

	if (!ProjectileRow->FireEffect.IsNull() && ProjectileRow->FireEffect.RowName != NAME_None)
	{
		AEffect* Effect = GetWorld()->SpawnActorDeferred<AEffect>(AEffect::StaticClass(), SocketTransform, this, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const FEffectDataTableRow* EffectDataTableRow = ProjectileRow->FireEffect.GetRow<FEffectDataTableRow>(TEXT(""));
		ensure(EffectDataTableRow);
		Effect->SetEffectData(EffectDataTableRow);
		Effect->FinishSpawning(SocketTransform, true);
	}
	/*if (EffectClass)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.Instigator = this;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(EffectClass, SocketTransform, ActorSpawnParameters);
	}*/

	ATankGameModeBase* GameMode = Cast<ATankGameModeBase>(GetWorld()->GetAuthGameMode());
	ensure(GameMode);
	AProjectile* NewProjectile = GameMode->GetProjectilePool().New<AProjectile>(SocketTransform,
		[this](AProjectile* NewActor)
		{
			NewActor->SetProjectileData(ProjectileRow);
		}
	, true, this, this);
}

// Called when the game starts or when spawned
void ANewTank::BeginPlay()
{
	Super::BeginPlay();
	ensure(UI);
	ZoomInWidget = CreateWidget<UUserWidget>(GetWorld(), UI);

	UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	ProjectileRow = DataSubsystem->FindProjectile(ProjectileName);
}

// Called every frame
void ANewTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANewTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


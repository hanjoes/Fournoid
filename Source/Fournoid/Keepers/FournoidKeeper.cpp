// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Characters/FournoidCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "FournoidKeeper.h"


// Sets default values
AFournoidKeeper::AFournoidKeeper()
: KeeperStickDistance(500.0f), KeeperPropelDistance(100.0f), KeeperMovementSpeed(1000.0f), KeeperHoverFalloff(10.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("KeeperFacingArrow"));
	SetRootComponent(ArrowComp);
	
	KeeperSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("KeeperSphereComp"));
	KeeperSphereComp->BodyInstance.SetCollisionProfileName("OverlapAll");
	KeeperSphereComp->AttachParent = ArrowComp;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeeperMesh"));
	StaticMeshComp->SetCollisionProfileName("NoCollision");
	StaticMeshComp->AttachParent = KeeperSphereComp;
	StaticMeshComp->bCastDynamicShadow = true;
	StaticMeshComp->CastShadow = true;
	
	KeeperMovement = CreateDefaultSubobject<UMovementComponent>(TEXT("KeeperMovement"));
	KeeperMovement->UpdatedComponent = KeeperSphereComp;
	
	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AFournoidKeeper::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFournoidKeeper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	auto NewLocation = GetActorLocation();
	auto DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	NewLocation.Z += DeltaHeight * KeeperHoverFalloff;
	SetActorLocation(NewLocation);
	
	RunningTime += DeltaTime;
	
//	FollowMaster(DeltaTime);
}

// Called to bind functionality to input
void AFournoidKeeper::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AFournoidKeeper::SetKeeperMaster(AFournoidCharacter *Master)
{
	MasterCharacter = Master;
}

void AFournoidKeeper::FollowMaster(float DeltaTime)
{
	// Make sure the keeper's distance to master is within KeeperFollowDistance
	if (MasterCharacter)
	{
		auto MyLocaiton = StaticMeshComp->GetComponentLocation();
		auto MasterLocation = MasterCharacter->GetRootComponent()->GetComponentLocation();
		auto DirectionVector = MasterLocation - MyLocaiton;
		
		// Get direction and distance from this keeper to the master.
		FVector Direction;
		float Distance;
		DirectionVector.ToDirectionAndLength(Direction, Distance);
		// Lerp velocity and move keeper towards character
		float Velocity = UKismetMathLibrary::Lerp(.0f, KeeperMovementSpeed, FMath::Abs(((Distance - KeeperPropelDistance) / KeeperStickDistance)));
		KeeperMovement->MoveUpdatedComponent(Direction * Velocity * DeltaTime, FQuat(), false);
	}
}

void AFournoidKeeper::SetKeeperMovementSpeed(float NewSpeed)
{
	KeeperMovementSpeed = NewSpeed;
}

void AFournoidKeeper::SetKeeperStickDistance(float NewDistance)
{
	KeeperStickDistance = NewDistance;
}

void AFournoidKeeper::SetKeeperPropelDistance(float NewDistance)
{
	KeeperPropelDistance = NewDistance;
}

void AFournoidKeeper::SetKeeperHoverFalloff(float NewFalloff)
{
	KeeperHoverFalloff = NewFalloff;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Bullets/FournoidBullet.h"
#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetupCollisionBehavior();
	PatrolLocation = FVector(-1,-1,-1);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void AEnemyCharacter::SetupCollisionBehavior()
{
}

void AEnemyCharacter::ReceiveDamage(float Damage)
{
	Super::ReceiveDamage(Damage);
	if(IsDead()){
		FTimerHandle UnusedHandle;
		DetachFromControllerPendingDestroy();
		SetLifeSpan(2.f);
	}
}

//This can be a function for the base class, AFounoidCharacter, as well as related variables
void AEnemyCharacter:: OnFire(){
	FournoidUtils::RedMessage("Firing");
	if (BulletClass != NULL)
	{
		// Get the actors rotation caused by control in world space.
		const FRotator SpawnRotation = GetControlRotation();
		// Tarnsform the SpawnOffset from local space to world space.
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(SpawnOffset);
		
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AFournoidBullet>(BulletClass, SpawnLocation, SpawnRotation);
		}
	}
}


FVector AEnemyCharacter::GetPatrolLoc(){
	return PatrolLocation;
}

TQueue<FVector>*
AEnemyCharacter::GetEnemyLocs(){
	return &EnemyLocations;
}

void
AEnemyCharacter::SetPatrolLoc(FVector Location){
	PatrolLocation = Location;
}


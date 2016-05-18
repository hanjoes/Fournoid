// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Weapons/FournoidWeapon.h"
#include "Bullets/FournoidBullet.h"
#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AEnemyCharacter::IsFirstPerson() const
{
	return false;
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
	if( IsDead() )
	{
		StopFire();
	}
	else
	{
		ReloadStore();
	}
}

//This can be a function for the base class, AFounoidCharacter, as well as related variables
void AEnemyCharacter:: StartFire()
{
	Super::StartFire();
}

void AEnemyCharacter:: StopFire()
{
	Super::StopFire();
}

float AEnemyCharacter::GetPatrolRadius()
{
	return PatrolRadius;
}

int32 AEnemyCharacter::ReloadStore()
{
	auto CurrWeapon = GetWeaponActor();
	if ( CurrentWeapon )
	{
    	int32 NumStore = CurrWeapon->GetCurrentStoreSize();
    	if ( NumStore <= 0 )
		{
    		CurrWeapon->AddCurrentStore(30);
    	}
    	
    	return CurrWeapon->GetCurrentStoreSize();
	}
	return 0;
}

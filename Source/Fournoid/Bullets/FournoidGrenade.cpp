// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidGrenade.h"
#include "GameFramework/DamageType.h"


AFournoidGrenade::AFournoidGrenade()
: AFournoidBullet()
{
	// Grenade can bounce
	BulletMovementComp->bShouldBounce = true;
	BulletMovementComp->InitialSpeed = 1500.f;
	BulletMovementComp->MaxSpeed = 1500.f;
	
	// Default values
	CoreDamage = 100.f;
	MaximalRadius = 500.f;
	MinimalRadius = 1000.f;
	
}

void AFournoidGrenade::OnHit(AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
}


void AFournoidGrenade::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	auto World = GetWorld();
	if ( World )
	{
		if ( ExplosionEmitter )
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionEmitter, GetTransform());
			UGameplayStatics::ApplyRadialDamageWithFalloff(this, CoreDamage, CoreDamage / 10.f, GetActorLocation(), MaximalRadius, MinimalRadius, 4.f, UDamageType::StaticClass(), TArray<AActor*>(), this, GetInstigatorController());
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidBullet.generated.h"

UCLASS()
class FOURNOID_API AFournoidBullet : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFournoidBullet();
	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	
	//////////////////////////////////////////////////////////////////////////
	// Damage
	
	/** called when projectile hits something */
	UFUNCTION()
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/** Impulse applied on hitting any rigid body  */
	UPROPERTY(EditAnywhere, Category=Damage)
	float BulletImpulseStrength;
	
	/** Damage caused on hit */
	UPROPERTY(EditAnywhere, Category=Damage)
	float BulletDamage;
	
protected:
	
	//////////////////////////////////////////////////////////////////////////
	// Components
	
	/** USphereComponent used for hit detection */
	UPROPERTY(VisibleDefaultsOnly, Category=Components)
	USphereComponent* BulletSphereComp;
	
	/** The mesh displayed */
	UPROPERTY(VisibleDefaultsOnly, Category=Components)
	UStaticMeshComponent* BulletMeshComp;
	
	/** Projectile movement component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Components)
	class UProjectileMovementComponent* BulletMovementComp;
	
	/** The pariticle system associated with the bullet */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Components)
	class UParticleSystemComponent* BulletParticleComp;
	
	//////////////////////////////////////////////////////////////////////////
	// Components
	
	/** Particle system played at the location of hit */
	UPROPERTY(EditDefaultsOnly, Category=FX)
	UParticleSystem* HitEmitter;
};

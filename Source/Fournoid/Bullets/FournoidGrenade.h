// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullets/FournoidBullet.h"
#include "FournoidGrenade.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidGrenade : public AFournoidBullet
{
	GENERATED_BODY()
	
public:
	
	AFournoidGrenade();
	
	/** Override default behavior which will cause the grenade to disappear */
	UFUNCTION()
	virtual void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	/** Overriden to cause damage to sourroundings */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	
	/** The particle system spawned at the place where grenade is destroyed */
	UPROPERTY(EditDefaultsOnly, Category=FX)
	UParticleSystem* ExplosionEmitter;
	
	/** Damage at the core of explosion */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float CoreDamage;
	
	/** the radius causing minimal damage */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float MinimalRadius;
	
	/** the radius causing max damage */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	float MaximalRadius;
	
	/** type of damage */
	UPROPERTY(EditDefaultsOnly, Category=Damage)
	TSubclassOf<UDamageType> DamageType;
	
};

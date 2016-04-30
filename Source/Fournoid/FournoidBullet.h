// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidBullet.generated.h"

UCLASS()
class FOURNOID_API AFournoidBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFournoidBullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	FORCEINLINE USphereComponent* GetSphereComponent() const { return BulletSphereComp; }

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	USphereComponent* BulletSphereComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	UStaticMeshComponent* BulletMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	float BulletImpulseStrength;
	
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	float BulletDamage;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* BulletMovementComp;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidBullet.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFournoidBullet::AFournoidBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize bullet capsule component.
	BulletSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	BulletSphereComp->BodyInstance.SetCollisionProfileName("Projectile");
	// Setup bullet hit
	BulletSphereComp->SetNotifyRigidBodyCollision(true);
	BulletSphereComp->OnComponentHit.AddDynamic(this, &AFournoidBullet::OnHit);
	// Player can't walk on it
	BulletSphereComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	BulletSphereComp->CanCharacterStepUpOn = ECB_No;
	RootComponent = BulletSphereComp;
	
	// Create the bullet's static mesh component.
	BulletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMeshComp->AttachParent = BulletSphereComp;
	BulletMeshComp->bCastDynamicShadow = false;
	BulletMeshComp->CastShadow = false;
	BulletMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BulletMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	BulletMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComp"));
	BulletMovementComp->UpdatedComponent = BulletSphereComp;
	BulletMovementComp->InitialSpeed = 3000.f;
	BulletMovementComp->MaxSpeed = 3000.f;
	BulletMovementComp->bRotationFollowsVelocity = true;
	BulletMovementComp->bShouldBounce = false;
	
	// Setup a particle system component associated with the bullet.
	BulletParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletParticleSystem"));
	BulletParticleComp->AttachParent = BulletSphereComp;
	
	
	bReplicates = true;
	bReplicateMovement = true;
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.f;
	BulletImpulseStrength = 10.f;
	BulletDamage = 25.f;
}

// Called when the game starts or when spawned
void AFournoidBullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFournoidBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFournoidBullet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ( OtherActor && (OtherActor != this) )
	{
		// Check for Simulating Physics or there will be warning
		if ( OtherComp && OtherComp->IsSimulatingPhysics() )
		{
    		OtherComp->AddImpulseAtLocation(GetVelocity() * BulletImpulseStrength, GetActorLocation());
		}
		
		// Only cause damage when not hitting the instigator
		if ( Instigator && (OtherActor != Instigator) )
		{
			FPointDamageEvent PointDmg;
			PointDmg.DamageTypeClass = UDamageType::StaticClass();
			PointDmg.HitInfo = Hit;
			PointDmg.ShotDirection = FVector::ZeroVector;
			PointDmg.Damage = BulletDamage;
    		
    		OtherActor->TakeDamage(PointDmg.Damage, PointDmg, GetInstigatorController(), this);
    		if ( HitEmitter )
    		{
    			UE_LOG(Fournoid, Warning, TEXT("Spawning Emitter"));
				UGameplayStatics::SpawnEmitterAtLocation(this, HitEmitter, GetActorLocation());
    		}
		}
		
		
		
		Destroy();
	}
}

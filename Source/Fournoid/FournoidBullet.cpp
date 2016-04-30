// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidBullet.h"
#include "EnemyCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AFournoidBullet::AFournoidBullet()
: BulletImpulseStrength(10.0f), BulletDamage(25.0f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize bullet capsule component.
	BulletSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	BulletSphereComp->BodyInstance.SetCollisionProfileName("Projectile");
	BulletSphereComp->AttachParent = BulletMeshComp;
	// Setup notification.
	BulletSphereComp->OnComponentHit.AddDynamic(this, &AFournoidBullet::OnHit);
	
	// Player can't walk on it (for now...)
	BulletSphereComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	BulletSphereComp->CanCharacterStepUpOn = ECB_No;
	
	RootComponent = BulletSphereComp;
	
	// Create the bullet's static mesh component.
	BulletMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMeshComp->AttachParent = BulletSphereComp;
	// no point for the bullet to cast any shadow.
	BulletMeshComp->bCastDynamicShadow = false;
	BulletMeshComp->CastShadow = false;
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	BulletMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComp"));
	BulletMovementComp->UpdatedComponent = BulletSphereComp;
	BulletMovementComp->InitialSpeed = 3000.f;
	BulletMovementComp->MaxSpeed = 3000.f;
	BulletMovementComp->bRotationFollowsVelocity = true;
	BulletMovementComp->bShouldBounce = false;
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFournoidBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFournoidBullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}


void AFournoidBullet::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * BulletImpulseStrength, GetActorLocation());
		IDamageable* DamageableObj = Cast<IDamageable>(OtherActor);
		if (DamageableObj) {
			DamageableObj->ReceiveDamage(BulletDamage);
		}
		
		//		Destroy();
	}
}
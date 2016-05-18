// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidPickup.h"


// Sets default values
AFournoidPickup::AFournoidPickup(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	UCapsuleComponent* CollisionComp = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CollisionComp"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	CollisionComp->SetCollisionObjectType(COLLISION_PICKUP);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;
	
	PickupPSC = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PickupFX"));
	PickupPSC->bAutoActivate = false;
	PickupPSC->bAutoDestroy = false;
	PickupPSC->AttachParent = RootComponent;
	
	bIsActive = false;
	RespawnTime = 5.f;
	
	//SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);

}

// Called when the game starts or when spawned
void AFournoidPickup::BeginPlay()
{
	Super::BeginPlay();
	Respawn();
	
}

// Called every frame
void AFournoidPickup::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AFournoidPickup::CanBePickedUp(AFournoidCharacter *TestPawn)const
{
	return TestPawn && TestPawn->IsAlive();
}


void AFournoidPickup::GivePickupTo(AFournoidCharacter *Pawn){
}

void AFournoidPickup::Respawn(){
	bIsActive = true;
	OnRespawned();
}

void AFournoidPickup::OnRespawned(){
	if (ActiveFX)
	{
		PickupPSC->SetTemplate(ActiveFX);
		PickupPSC->ActivateSystem();
	}
	else
	{
		PickupPSC->DeactivateSystem();
	}
}

void AFournoidPickup::PickupOnTouch(class AFournoidCharacter *Pawn){
	FournoidUtils::GreenMessage("On Touch");
	if (bIsActive && Pawn && Pawn->IsAlive() && !IsPendingKill())
	{
		if (CanBePickedUp(Pawn))
		{
			GivePickupTo(Pawn);
			if (!IsPendingKill())
			{
				bIsActive = false;
				OnPickedUp();
				
				if (RespawnTime > 0.0f)
				{
					GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &AFournoidPickup::Respawn, RespawnTime, false);
				}
			}
		}
	}
}

void AFournoidPickup::OnPickedUp(){
	PickupPSC->DeactivateSystem();

}

void AFournoidPickup::NotifyActorBeginOverlap(class AActor* Other){
	Super::NotifyActorBeginOverlap(Other);
	PickupOnTouch(Cast<AFournoidCharacter>(Other));
}

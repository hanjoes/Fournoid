// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidOrbiter.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFournoidOrbiter::AFournoidOrbiter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ArrowComp = CreateDefaultSubobject<UArrowComponent>("OrbiterArrow");
	RootComponent = ArrowComp;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("OrbiterMesh");
	Mesh->AttachParent = ArrowComp;
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	// Default values
	SpeedScale = 10.f;
}

void AFournoidOrbiter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFournoidOrbiter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	SelfRotate(DeltaTime);
	Orbit(DeltaTime);
	
	RunningTime += DeltaTime;
}

void AFournoidOrbiter::Orbit(float DeltaTime)
{
	if ( Parent )
	{
		auto DistFromParent = Parent->GetDistanceTo(this);
		auto ParentForwardVec = Parent->GetActorForwardVector();
		auto OffsetFromParent = DistFromParent * ParentForwardVec;
		auto NewLocation = Parent->GetActorLocation() + OffsetFromParent;
		UE_LOG(Fournoid, Warning, TEXT("ParentLoc: %s, Dist: %f, Offset: %s, NewLoc: %s"), *(Parent->GetActorLocation().ToString()), DistFromParent,*(OffsetFromParent.ToString()), *(NewLocation.ToString()));
		SetActorLocation(Parent->GetActorLocation() + OffsetFromParent);
	}
}

void AFournoidOrbiter::SelfRotate(float DeltaTime)
{
	auto CurrentRot = GetActorRotation();
	auto NewRot = CurrentRot.Add(.0f, DeltaTime * SpeedScale, .0f);
	SetActorRelativeRotation(NewRot);
}


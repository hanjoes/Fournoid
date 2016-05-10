// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidWeapon.h"


// Sets default values
AFournoidWeapon::AFournoidWeapon()
{
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = Mesh1P;
	
	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh3P"));
	Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->CastShadow = false;
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh3P->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	Mesh3P->AttachParent = Mesh1P;
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}

// Called when the game starts or when spawned
void AFournoidWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFournoidWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFournoidWeapon::SetOwningPawn(AFournoidCharacter* OwningChara)
{
	if (MyPawn != OwningChara)
	{
		// TODO: Not sure what Instigator does...
		Instigator = OwningChara;
		MyPawn = OwningChara;
		
		SetOwner(MyPawn);
	}
}

//////////////////////////////////////////////////////////////////////////
// Inventory/Weapon

void AFournoidWeapon::OnEquip()
{
	AttachWeaponToPawn();
}

void AFournoidWeapon::OnUnEquip()
{
	
}

void AFournoidWeapon::OnEnterInventory(AFournoidCharacter* OwningChara)
{
	SetOwningPawn(OwningChara);
}

void AFournoidWeapon::AttachWeaponToPawn()
{
	if (MyPawn)
	{
		DetachWeaponFromPawn();
		
		// Let bOnlyOwnerSee, bOwnerNoSee determine visibility.
		auto AttachPoint = MyPawn->GetWeaponAttachPoint();
		
		// set 1st person mesh
		auto PawnMesh1P = MyPawn->GetPawnMesh(true);
		Mesh1P->SetHiddenInGame(false);
		Mesh1P->AttachTo(PawnMesh1P, AttachPoint);
		
		// set 3st person mesh
		auto PawnMesh3P = MyPawn->GetPawnMesh(false);
		Mesh3P->SetHiddenInGame(false);
		Mesh3P->AttachTo(PawnMesh3P, AttachPoint);
	}
}

void AFournoidWeapon::DetachWeaponFromPawn()
{
	
}

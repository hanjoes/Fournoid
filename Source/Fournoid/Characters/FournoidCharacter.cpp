// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidCharacter.h"
#include "PlayerCharacter.h"
#include "FournoidMovementComponent.h"
#include "Bullets/FournoidBullet.h"
#include "Weapons/FournoidWeapon.h"
#include "Keepers/FournoidKeeper.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


AFournoidCharacter::AFournoidCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UFournoidMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->AttachParent = GetCapsuleComponent();
	Mesh1P->bOnlyOwnerSee = true;
	Mesh1P->bOwnerNoSee = false;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Mesh1P->SetCollisionObjectType(ECC_Pawn);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Ignore);
	
	bReplicates = true;
	
	// Default values
	
	Health = 100.f;
	Stamina = 100.f;
	StaminaRegenRate = 15.f;
	StaminaConsumeRate = 30.f;
	SpeedBoostScale = 1.5f;
	DestroyLifeSpan = 10.f;
	bCharacterIsRunning = false;
}

void AFournoidCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnKeeper();
	SpawnInventory();
}

void AFournoidCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyInventory();
}

void AFournoidCharacter::StartRunning()
{
	if ( Role < ROLE_Authority )
	{
		ServerStartRunning();
	}
	else
	{
    	bCharacterIsRunning = true;
	}
}

void AFournoidCharacter::StopRunning()
{
	if ( Role < ROLE_Authority )
	{
		ServerStopRunning();
	}
	else
	{
    	bCharacterIsRunning = false;
	}
}

void AFournoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bCharacterIsRunning && (GetVelocity() != FVector::ZeroVector))
	{
		Stamina -= DeltaTime * StaminaConsumeRate;
		
		// If stamina is equal or below zero, stop running.
		if (Stamina <= 0.0f)
		{
			StopRunning();
		}
	}
	else
	{
		// regen only if stamina is not full
		if (Stamina < 100.f)
		{
			Stamina += DeltaTime * StaminaRegenRate;
			Stamina = FMath::Min(Stamina, 100.f);
		}
	}
}

void AFournoidCharacter::SpawnKeeper()
{
}

void AFournoidCharacter::PossessedBy(class AController *InController)
{
	Super::PossessedBy(InController);
}

void AFournoidCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	DOREPLIFETIME_CONDITION( AFournoidCharacter, Inventory, COND_OwnerOnly );
	
	// everyone
	DOREPLIFETIME( AFournoidCharacter, CurrentWeapon );
}

void AFournoidCharacter::SpawnInventory()
{
	if (Role < ROLE_Authority)
	{
		return;
	}
	
	int32 NumWeaponClasses = WeaponClasses.Num();
	for (int32 i = 0; i < NumWeaponClasses; ++i)
	{
		if (WeaponClasses[i])
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			auto NewWeapon = GetWorld()->SpawnActor<AFournoidWeapon>(WeaponClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}
	
	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
	
}

void AFournoidCharacter::AddWeapon(AFournoidWeapon *NewWeapon)
{
	if (NewWeapon && Role == ROLE_Authority)
	{
		Inventory.AddUnique(NewWeapon);
		NewWeapon->OnEnterInventory(this);
	}
}

void AFournoidCharacter::EquipWeapon(AFournoidWeapon *Weapon)
{
	if (Weapon)
	{
		if (Role == ROLE_Authority)
		{
			SetCurrentWeapon(Weapon);
		}
		else
		{
			ServerEquipWeapon(Weapon);
		}
	}
}

bool AFournoidCharacter::ServerEquipWeapon_Validate(AFournoidWeapon *Weapon)
{
	return true;
}

void AFournoidCharacter::ServerEquipWeapon_Implementation(AFournoidWeapon *Weapon)
{
	EquipWeapon(Weapon);
}

void AFournoidCharacter::SetCurrentWeapon(class AFournoidWeapon *Weapon)
{
	// Unequip the current weapon if already equipped.
	if (CurrentWeapon)
	{
		CurrentWeapon->OnUnEquip();
	}
	
	CurrentWeapon = Weapon;
	
	if (Weapon) {
		Weapon->SetOwningPawn(this);
    	Weapon->OnEquip();
	}
}

USkeletalMeshComponent* AFournoidCharacter::GetPawnMesh(bool IsFirstPerson) const
{
	return IsFirstPerson ? Mesh1P : GetMesh();
}

FName AFournoidCharacter::GetWeaponAttachPoint() const
{
	return WeaponSocketName;
}

bool AFournoidCharacter::IsDead() const
{
	return bIsDead;
}

bool AFournoidCharacter::IsAlive() const
{
	return !bIsDead;
}

void AFournoidCharacter::UpdatePawnMesh()
{
	bool bFirstPerson = IsFirstPerson();

	Mesh1P->MeshComponentUpdateFlag = !bFirstPerson ? EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered : EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	Mesh1P->SetOwnerNoSee(!bFirstPerson);

	GetMesh()->MeshComponentUpdateFlag = bFirstPerson ? EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered : EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetOwnerNoSee(bFirstPerson);
}

void AFournoidCharacter::OnRep_CurrentWeapon()
{
	SetCurrentWeapon(CurrentWeapon);
}

void AFournoidCharacter::StartFire()
{
	if ( CurrentWeapon )
	{
		CurrentWeapon->StartFire();
	}
}

void AFournoidCharacter::StopFire()
{
	if ( CurrentWeapon )
	{
		CurrentWeapon->StopFire();
	}
}

bool AFournoidCharacter::IsFirstPerson() const
{
	return IsLocallyControlled() && IsAlive();
}

void AFournoidCharacter::Die()
{
	if (Role == ROLE_Authority)
	{
		ServerDie();
	}
	OnDeath();
}

bool AFournoidCharacter::ServerDie_Validate()
{
	return true;
}

void AFournoidCharacter::ServerDie_Implementation()
{
	OnDeath();
}

void AFournoidCharacter::OnDeath()
{
	bIsDead = true;
	UpdatePawnMesh();
	DetachFromControllerPendingDestroy();
	
	SetLifeSpan(DestroyLifeSpan);
}

void AFournoidCharacter::OnRep_bIsDead()
{
	Die();
}

void AFournoidCharacter::DestroyInventory()
{
	for (int32 i = 0; i < Inventory.Num(); ++i)
	{
		Inventory[i]->Destroy();
	}
	Inventory.Empty();
}

bool AFournoidCharacter::ServerStartRunning_Validate()
{
	return true;
}

void AFournoidCharacter::ServerStartRunning_Implementation()
{
	StartRunning();
}

bool AFournoidCharacter::ServerStopRunning_Validate()
{
	return true;
}

void AFournoidCharacter::ServerStopRunning_Implementation()
{
	StopRunning();
}

float AFournoidCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0.0f)
	{
		Die();
	}
	
	if ( EventInstigator )
	{
    	auto InstigatorPlayer = Cast<APlayerCharacter>(EventInstigator->GetPawn());
		if ( InstigatorPlayer )
		{
        	InstigatorPlayer->PlayHitSound();
		}
	}
	
	return Damage;
}


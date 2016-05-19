// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Bullets/FournoidBullet.h"
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
	
	// Default values
	CurrentState = WeaponState::WS_Idle;
	ReloadDuration = 2.f;
	FiringRate = .3f;
	InitialBulletStore = 60;
	ClipCapacity = 30;
	StoreCapacity = 5*ClipCapacity;
}

// Called when the game starts or when spawned
void AFournoidWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentClipSize = ClipCapacity;
	CurrentStoreSize = InitialBulletStore;
}

// Called every frame
void AFournoidWeapon::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
}

void AFournoidWeapon::SetOwningPawn(AFournoidCharacter* OwningChara)
{
	if (MyPawn != OwningChara)
	{
		Instigator = OwningChara;
		MyPawn = OwningChara;
		
		SetOwner(OwningChara);
	}
}

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
		
		auto AttachPoint = MyPawn->GetWeaponAttachPoint();
		
		// Let bOnlyOwnerSee, bOwnerNoSee determine visibility.
		auto PawnMesh1P = MyPawn->GetPawnMesh(true);
		if (Mesh1P && PawnMesh1P)
		{
			Mesh1P->SetHiddenInGame(false);
			Mesh1P->AttachTo(PawnMesh1P, AttachPoint);
		}
		
		auto PawnMesh3P = MyPawn->GetPawnMesh(false);
		if (Mesh3P && PawnMesh3P)
		{
			Mesh3P->SetHiddenInGame(false);
			Mesh3P->AttachTo(PawnMesh3P, AttachPoint);
		}
	}
}

void AFournoidWeapon::DetachWeaponFromPawn()
{
	if (Mesh1P)
	{
		Mesh1P->DetachFromParent();
		Mesh1P->SetHiddenInGame(true);
	}
	if (Mesh3P)
	{
		Mesh3P->DetachFromParent();
		Mesh3P->SetHiddenInGame(true);
	}
}

void AFournoidWeapon::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	
	DOREPLIFETIME(AFournoidWeapon, MyPawn);
	
	DOREPLIFETIME(AFournoidWeapon, CurrentStoreSize);
	DOREPLIFETIME(AFournoidWeapon, CurrentClipSize);
}

void AFournoidWeapon::OnRep_MyPawn()
{
	if (MyPawn)
	{
		OnEnterInventory(MyPawn);
	}
}

USkeletalMeshComponent* AFournoidWeapon::GetWeaponMesh() const
{
	return (MyPawn && MyPawn->IsFirstPerson()) ? Mesh1P : Mesh3P;
}

FVector AFournoidWeapon::GetMuzzleLocation() const
{
	auto UseMesh = GetWeaponMesh();
	return UseMesh->GetSocketLocation(MuzzleSocketName);
}

void AFournoidWeapon::StartFire()
{
	if ( MyPawn->IsFirstPerson() && (IsClipEmpty() && IsStoreEmpty()) )
	{
		PlayWeaponSound(EmptySound);
		return;
	}
	
	if ( Role < ROLE_Authority )
	{
		ServerStartFire();
		return;
	}
	
	if ( CurrentState == WeaponState::WS_Idle )
	{
    	SetWeaponState(WeaponState::WS_Firing);
	}
}

void AFournoidWeapon::StopFire()
{
	if ( Role < ROLE_Authority )
	{
		ServerStopFire();
	}
	
	if ( CurrentState == WeaponState::WS_Firing )
	{
    	SetWeaponState(WeaponState::WS_Idle);
	}
}

void AFournoidWeapon::OnFireStarted()
{
	// Not checking last fire time for simplicity, so players can
	// cheat if they have a finger that's quick enough...
	FireBullet();
}

bool AFournoidWeapon::ServerStartFire_Validate()
{
	return true;
}

void AFournoidWeapon::ServerStartFire_Implementation()
{
	StartFire();
}

bool AFournoidWeapon::ServerStopFire_Validate()
{
	return true;
}

void AFournoidWeapon::ServerStopFire_Implementation()
{
	StopFire();
}

void AFournoidWeapon::OnFireStopped()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_HandleFireBullet);
}

void AFournoidWeapon::FireBullet()
{
	if ( BulletClass )
	{
		if ( MyPawn )
		{
			const auto SpawnRotation = MyPawn->GetControlRotation();
			const auto SpawnLocation = GetMuzzleLocation();
			const auto World = GetWorld();
			
			if ( World )
			{
				if ( Role == ROLE_Authority )
				{
					if ( !IsClipEmpty() )
					{
        				auto SpawnedBullet = World->SpawnActor<AFournoidBullet>(BulletClass, SpawnLocation, SpawnRotation);
        				SpawnedBullet->Instigator = Instigator;
        				PlayShootingFX();
    					CurrentClipSize -= 1;
            			GetWorldTimerManager().SetTimer(TimerHandle_HandleFireBullet, this, &AFournoidWeapon::FireBullet, FiringRate, false);
					}
					else
					{
						StartReloading();
					}
				}
			}
		}
	}
}

void AFournoidWeapon::PlayWeaponSound(USoundBase* Sound)
{
	if ( Sound )
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sound, GetActorLocation());
	}
}

void AFournoidWeapon::PlayFireAnimation()
{
	if ( FireAnimation )
	{
		auto AnimInstance = Mesh1P->GetAnimInstance();
		if ( AnimInstance )
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
	
	if ( FireEmitter )
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, FireEmitter, GetMuzzleLocation());
	}
}

void AFournoidWeapon::SetWeaponState(WeaponState NewState)
{
	const auto PrevState = CurrentState;
	
	if ( PrevState == WeaponState::WS_Firing && NewState != WeaponState::WS_Firing )
	{
		OnFireStopped();
	}
	
	CurrentState = NewState;
	
	if ( CurrentState == WeaponState::WS_Firing )
	{
		OnFireStarted();
	}
}

void AFournoidWeapon::PlayShootingFX_Implementation()
{
	if ( GetNetMode() != NM_DedicatedServer )
	{
		PlayWeaponSound(FireSound);
		PlayFireAnimation();
	}
}

bool AFournoidWeapon::IsClipEmpty()
{
	return CurrentClipSize == 0;
}

bool AFournoidWeapon::IsClipFull()
{
	return CurrentClipSize == ClipCapacity;
}

bool AFournoidWeapon::IsStoreEmpty()
{
	return CurrentStoreSize == 0;
}

bool AFournoidWeapon::IsStoreFull()
{
	return CurrentStoreSize >= StoreCapacity;
}

void AFournoidWeapon::StartReloading()
{
	if ( CurrentState == WeaponState::WS_Idle || CurrentState == WeaponState::WS_Firing )
	{
		if ( !IsStoreEmpty() )
		{
    		SetWeaponState(WeaponState::WS_Reloading);
    		GetWorldTimerManager().SetTimer(TimerHandle_HandleReloadWeapon, this, &AFournoidWeapon::OnReloadFinished, ReloadDuration, false);
		}
	}
}

void AFournoidWeapon::OnReloadFinished()
{
	if ( CurrentState == WeaponState::WS_Idle || CurrentState == WeaponState::WS_Reloading )
	{
		//FournoidUtils::GreenMessage(TEXT("Reload finished..."));
		auto RequiredAmmo = FMath::Min(ClipCapacity - CurrentClipSize, CurrentStoreSize);
		CurrentStoreSize -= RequiredAmmo;
		CurrentClipSize += RequiredAmmo;
		
		SetWeaponState(WeaponState::WS_Idle);
	}
}

void AFournoidWeapon::Reload()
{
	StartReloading();
}

void AFournoidWeapon::AddCurrentStore(int32 StoreSize)
{
	CurrentStoreSize += StoreSize;
	if ( IsStoreFull() )
	{
		CurrentStoreSize = StoreCapacity;
	}
}

void AFournoidWeapon::SetStoreCapacity(int32 Capacity)
{
	StoreCapacity = Capacity;
}

void AFournoidWeapon::SetClipCapacity(int32 Capacity)
{
	ClipCapacity = Capacity;
}

void AFournoidWeapon::SetCurrentClipSize(int32 ClipSize)
{
	CurrentClipSize = ClipSize;
}
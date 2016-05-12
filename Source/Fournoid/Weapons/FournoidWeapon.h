// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidWeapon.generated.h"

UENUM()
enum class WeaponState : uint8
{
	WS_Idle,
	WS_Firing,
	WS_Reloading,
	WS_Equipping,
};

UCLASS(Abstract, BluePrintable)
class FOURNOID_API AFournoidWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFournoidWeapon();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;
	
	void SetOwningPawn( class AFournoidCharacter* OwningChara );
	
	/** Returns the muzzle location according to socket */
	FVector GetMuzzleLocation() const;
	
	//////////////////////////////////////////////////////////////////////////
	// Inventory
	
public:
	
	/** Called when the weapon is equipped */
	virtual void OnEquip();
	
	/** Called when the weapon is un-equipped */
	virtual void OnUnEquip();
	
	/** Called when the weapon entered the character inventory */
	virtual void OnEnterInventory(class AFournoidCharacter* OwnerChara);
	
	/** Attach the mesh to character according to perspective */
	void AttachWeaponToPawn();
	
	/** Remove the weapon from the attached character */
	void DetachWeaponFromPawn();
	
	/** The Pawn that's wielding the weapon */
	UPROPERTY(Transient, ReplicatedUsing=OnRep_MyPawn)
	class AFournoidCharacter* MyPawn;
	
	//////////////////////////////////////////////////////////////////////////
	// Mesh
	
private:
	
	/** Mesh for 1st person perspective */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	
	/** Mesh for 3st person perspective */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh3P;
	
	USkeletalMeshComponent* GetWeaponMesh() const;
	
	//////////////////////////////////////////////////////////////////////////
	// Fire
	
public:
	
	/** Called by APawn to start firing the weapon */
	virtual void StartFire();
	
	/** Called by APawn to stop firing the weapon */
	virtual void StopFire();
	
protected:
	
	/** Fire bullets */
	virtual void FireBullet();
	
	/** Plays the fire montage */
	void PlayFireAnimation();
	
	/** Plays the fire sound */
	void PlayFireSound();
	
	/** Sound to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Fire)
	class USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Fire)
	class UAnimMontage* FireAnimation;
	
	/** Muzzle socket name */
	UPROPERTY(EditDefaultsOnly, Category=Fire)
	FName MuzzleSocketName;
	
	/** Rate at which the weapon fire */
	UPROPERTY(EditDefaultsOnly, Category=Fire)
	float FiringRate;
	
	/** Bullet class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Fire)
	TSubclassOf<class AFournoidBullet> BulletClass;
	
	//////////////////////////////////////////////////////////////////////////
	// Weapon State
	
	/** Called when the weapon starts firing */
	virtual void OnFireStarted();
	
	/** Called when the weapon stops firing */
	virtual void OnFireStopped();
	
	/** Update weapon state */
	void SetWeaponState( WeaponState NewState );
	
	UPROPERTY()
	WeaponState CurrentState;
	
	//////////////////////////////////////////////////////////////////////////
	// Timer Related
	
	/** Keep track of the timer set for FireBullet */
	FTimerHandle TimerHandle_HandleFireBullet;
	
	//////////////////////////////////////////////////////////////////////////
	// Replicate
	
protected:
	
	/** MyPawn replication callback. */
	UFUNCTION()
	void OnRep_MyPawn();
	
};

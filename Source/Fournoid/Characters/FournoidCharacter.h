// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Damageable.h"
#include "GameFramework/Character.h"
#include "FournoidCharacter.generated.h"

class UInputComponent;

UCLASS(Abstract)
class AFournoidCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()
	
	//////////////////////////////////////////////////////////////////////////
	// Basic/Lifecycles
	
public:
	AFournoidCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void PossessedBy(class AController *InController) override;
	
	void StartRunning();
	
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartRunning();
	
	void StopRunning();
	
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopRunning();
	
	bool IsFirstPerson() const;
	
	void Die();
	
protected:
	
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDie();
	
	void OnDeath();
	
	//////////////////////////////////////////////////////////////////////////
	// Keeper
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category=Keeper)
	TSubclassOf<class AFournoidKeeper> KeeperClass;
	
	virtual void SpawnKeeper();
	
	//////////////////////////////////////////////////////////////////////////
	// Status
	
public:
	
	/** Returns whether the player is dead */
	UFUNCTION(BlueprintPure, Category=Stats)
	bool IsDead() const;
	
	/** Returns whether the player is alive */
	UFUNCTION(BlueprintPure, Category=Stats)
	bool IsAlive() const;
	
public:
	
	FORCEINLINE float GetCharacterHealth() const { return Health; }
	
	FORCEINLINE float GetCharacterStamina() const { return Stamina; }
	
	FORCEINLINE float GetStaminaRegenRate() const { return StaminaRegenRate; }
	
	FORCEINLINE float GetStaminaConsumeRate() const { return StaminaConsumeRate; }
	
	FORCEINLINE float GetSpeedScale() const { return SpeedBoostScale; }
	
	FORCEINLINE float GetDestroyLifeSpan() const { return DestroyLifeSpan; }
	
	FORCEINLINE bool CharacterIsRunning() const { return bCharacterIsRunning; }
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float Stamina;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float StaminaRegenRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float StaminaConsumeRate;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float SpeedBoostScale;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category=Stats)
	float DestroyLifeSpan;
	
	bool bCharacterIsRunning;
	
	UPROPERTY(ReplicatedUsing=OnRep_bIsDead)
	bool bIsDead;
	
	//////////////////////////////////////////////////////////////////////////
	// Inventory/Weapon
	
public:
	
	FName GetWeaponAttachPoint() const;
	
protected:
	void SpawnInventory();
	
	void AddWeapon(class AFournoidWeapon* NewWeapon);
	
	void EquipWeapon(class AFournoidWeapon* Weapon);
	
	void SetCurrentWeapon(class AFournoidWeapon* Weapon);
	
	void DestroyInventory();
	
	UFUNCTION(Reliable, WithValidation, Server)
	void ServerEquipWeapon(class AFournoidWeapon* Weapon);
	
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	TArray<TSubclassOf<class AFournoidWeapon>> WeaponClasses;
	
	UPROPERTY(Transient, Replicated)
	TArray<class AFournoidWeapon*> Inventory;
	
	UPROPERTY(EditDefaultsOnly, Category=Weapon)
	FName WeaponSocketName;
	
	UPROPERTY(Transient, ReplicatedUsing=OnRep_CurrentWeapon)
	class AFournoidWeapon* CurrentWeapon;
	
	//////////////////////////////////////////////////////////////////////////
	// IDamageable
	
public:
	void ReceiveDamage(float Damage) override;
	
	//////////////////////////////////////////////////////////////////////////
	// Mesh
	
public:
	
	USkeletalMeshComponent* GetPawnMesh(bool IsFirstPerson) const;
	
protected:
	
	void UpdatePawnMesh();
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	
	//////////////////////////////////////////////////////////////////////////
	// Weapon Fire
	
	virtual void StartFire();
	
	virtual void StopFire();
	
	void FireWeapon();
	
	//////////////////////////////////////////////////////////////////////////
	// Replicate
	
protected:
	
	UFUNCTION()
	void OnRep_CurrentWeapon();
	
	UFUNCTION()
	void OnRep_bIsDead();
	
};

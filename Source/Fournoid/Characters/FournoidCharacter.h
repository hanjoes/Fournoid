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
	// Basic Behavior
	
public:
	AFournoidCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void PossessedBy(class AController *InController) override;
	
	void StartRunning();
	
	void StopRunning();
	
	void Die();
	
	bool IsFirstPerson() const;

	/** Take damage, handle death */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
	//////////////////////////////////////////////////////////////////////////
	// Keeper
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category=Keeper)
	TSubclassOf<class AFournoidKeeper> KeeperClass;
	
	virtual void SpawnKeeper();
	
	//////////////////////////////////////////////////////////////////////////
	// Status
	
public:
	
	UFUNCTION(BlueprintPure, Category=Stats)
	bool IsDead() const;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	float Stamina;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	float StaminaRegenRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	float StaminaConsumeRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	float SpeedBoostScale;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	bool bCharacterIsRunning;
	
	UPROPERTY(Replicated)
	bool bIsDead;
	
	FORCEINLINE float GetCharacterHealth() const { return Health; }
	
	FORCEINLINE float GetCharacterStamina() const { return Stamina; }
	
	FORCEINLINE float GetStaminaRegenRate() const { return StaminaRegenRate; }
	
	FORCEINLINE float GetStaminaConsumeRate() const { return StaminaConsumeRate; }
	
	FORCEINLINE float GetSpeedScale() const { return Stamina; }
	
	FORCEINLINE bool CharacterIsRunning() const { return bCharacterIsRunning; }
	
	//////////////////////////////////////////////////////////////////////////
	// Inventory/Weapon
	
public:
	
	FName GetWeaponAttachPoint() const;
	
protected:
	void SpawnInventory();
	
	void AddWeapon(class AFournoidWeapon* NewWeapon);
	
	void EquipWeapon(class AFournoidWeapon* Weapon);
	
	void SetCurrentWeapon(class AFournoidWeapon* Weapon);
	
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
	
};

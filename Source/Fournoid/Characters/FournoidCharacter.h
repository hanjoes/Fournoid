// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Character.h"
#include "FournoidCharacter.generated.h"

class UInputComponent;

UCLASS(Abstract)
class AFournoidCharacter : public ACharacter
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
	
	virtual bool IsFirstPerson() const;
	
	void Die(AController* InstigatorController);

	/** Take damage, handle death */
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
	
protected:
	
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDie(AController* InstigatorController);
	
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
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Replicated, Category=Stats)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Replicated, Category=Stats)
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
	
	void ReloadCurrentWeapon();

	FORCEINLINE AFournoidWeapon* GetWeaponActor() const { return CurrentWeapon; }
	
	void SetHealth(float NewHealth);
	
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
	// Components
	
public:
	
	USkeletalMeshComponent* GetPawnMesh(bool IsFirstPerson) const;
	
protected:
	
	void UpdatePawnMesh();
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	
	//////////////////////////////////////////////////////////////////////////
	// Weapon
	
public:
	
	/** Toss a nade, triggered by AIController or Player */
	virtual void Toss();
	
	/** Increase the number of grenades by a specific num */
	UFUNCTION(BlueprintCallable, Category=Grenade)
	void IncrementGrenade(int32 Num);
	
protected:
	
	/** Character starts firing, triggered by AIController or Player */
	virtual void StartFire();
	
	/** Character stops firing, triggered by AIController or Player */
	virtual void StopFire();
	
	/** Returns boolean indicates whether there are still grenades. */
	bool IsGrenadeStoreEmpty() const;
	
	/** [server] Toss grenade */
	UFUNCTION(Reliable, WithValidation, Server)
	void ServerToss();
	
	/** The grenade class */
	UPROPERTY(EditDefaultsOnly, Category=Grenade)
	TSubclassOf<class AFournoidGrenade> GrenadeClass;
	
	/** Grenades stored TODO: */
	UPROPERTY(VisibleAnywhere, Replicated, Category=Grenade)
	TArray<class AFournoidGrenade *> Grenades;
	
	/** Current number of grenades held by player */
	UPROPERTY(EditDefaultsOnly, Replicated, Category=Grenade)
	int32 GrenadeNum;
	
	//////////////////////////////////////////////////////////////////////////
	// Replicate
	
protected:
	
	UFUNCTION()
	void OnRep_CurrentWeapon();
	
	UFUNCTION()
	void OnRep_bIsDead();
	
};

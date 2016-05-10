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
	
public:
	AFournoidCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void PossessedBy(class AController *InController) override;
	
	void StartRunning();
	
	void StopRunning();
	
	//////////////////////////////////////////////////////////////////////////
	// Keeper
protected:
	
	UPROPERTY(EditDefaultsOnly, Category=Keeper)
	TSubclassOf<class AFournoidKeeper> KeeperClass;
	
	virtual void SpawnKeeper();
	
	//////////////////////////////////////////////////////////////////////////
	// Status
	
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category=Stats)
	bool bIsDead;
	
	FORCEINLINE float GetCharacterHealth() const { return Health; }
	
	FORCEINLINE float GetCharacterStamina() const { return Stamina; }
	
	FORCEINLINE float GetStaminaRegenRate() const { return StaminaRegenRate; }
	
	FORCEINLINE float GetStaminaConsumeRate() const { return StaminaConsumeRate; }
	
	FORCEINLINE float GetSpeedScale() const { return Stamina; }
	
	FORCEINLINE bool CharacterIsRunning() const { return bCharacterIsRunning; }
	
	FORCEINLINE bool IsDead() const { return bIsDead; }
	
	//////////////////////////////////////////////////////////////////////////
	// Inventory/Weapon
public:
	FORCEINLINE FName GetWeaponAttachPoint() const { return WeaponAttachPoint; }
	
protected:
	void SpawnInventory();
	
	void AddWeapon(class AFournoidWeapon* NewWeapon);
	
	void EquipWeapon(class AFournoidWeapon* Weapon);
	
	void SetCurrentWeapon(class AFournoidWeapon* Weapon);
	
	UPROPERTY(EditDefaultsOnly, Category=Inventory)
	TArray<TSubclassOf<class AFournoidWeapon>> WeaponClasses;
	
	UPROPERTY(Transient, Replicated)
	TArray<class AFournoidWeapon*> Inventory;
	
	UPROPERTY(EditDefaultsOnly, Category=Weapon)
	FName WeaponAttachPoint;
	
	class AFournoidWeapon* CurrentWeapon;
	
	/////////////////////////////////////////////////
	// IDamageable
public:
	void ReceiveDamage(float Damage) override;
	
	/////////////////////////////////////////////////
	// Mesh
public:
	
	USkeletalMeshComponent* GetPawnMesh(bool IsFirstPerson) const;
	
protected:
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;
	
};

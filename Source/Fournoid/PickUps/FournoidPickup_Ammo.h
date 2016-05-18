// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/FournoidPickup.h"
#include "FournoidPickup_Ammo.generated.h"
class AFournoidPickup;
/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidPickup_Ammo : public AFournoidPickup
{
	GENERATED_BODY()
	
public:
	AFournoidPickup_Ammo(const FObjectInitializer& ObjectInitializer);
	/** check if pawn can use this pickup */
	virtual bool CanBePickedUp(AFournoidCharacter* TestPawn) const override;
	bool IsForWeapon(UClass* WeaponClass);
	
protected:
	/** how much ammo does it give? */
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	int32 AmmoClips;
	
	/** which weapon gets ammo? */
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	TSubclassOf<AFournoidWeapon> WeaponType;
	
	/** give pickup */
	virtual void GivePickupTo(AFournoidCharacter* Pawn) override;
	

};

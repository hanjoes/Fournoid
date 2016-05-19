// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/FournoidPickup.h"
#include "FournoidPickup_Grenade.generated.h"
class AFournoidPickup;
/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidPickup_Grenade : public AFournoidPickup
{
	GENERATED_BODY()
	
public:
	AFournoidPickup_Grenade(const FObjectInitializer& ObjectInitializer);
	
	bool CanBePickedUp(AFournoidCharacter* TestPawn) const override;
	
	void GivePickupTo(AFournoidCharacter* Pawn) override;
	
protected:
	
	/** how much ammo does it give? */
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	int32 GrenadeNum;
};

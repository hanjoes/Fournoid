// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUps/FournoidPickup.h"
#include "FournoidPickup_Health.generated.h"
class AFournoidPickup;
/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidPickup_Health : public AFournoidPickup
{
	GENERATED_BODY()
	
public:
	AFournoidPickup_Health(const FObjectInitializer& ObjectInitializer);
	
	bool CanBePickedUp(AFournoidCharacter* TestPawn)const override;
	
	
protected:
	/** how much health does it give*/
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	int32 Health;
	
	/** give pick up*/
	virtual void GivePickupTo(AFournoidCharacter* Pawn)override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Characters/PlayerCharacter.h"
#include "FournoidPickup_Grenade.h"

AFournoidPickup_Grenade::AFournoidPickup_Grenade(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	GrenadeNum = 2;
}

bool AFournoidPickup_Grenade::CanBePickedUp(AFournoidCharacter *TestPawn) const
{
	if( TestPawn->IsA<APlayerCharacter>() ){
		return !TestPawn->IsGrenadeStoreFull();
	}
	return false;
}

void AFournoidPickup_Grenade::GivePickupTo(AFournoidCharacter *Pawn)
{
	if ( Pawn->IsA<APlayerCharacter>() ){
		Pawn->IncrementGrenade(GrenadeNum);
	}
}


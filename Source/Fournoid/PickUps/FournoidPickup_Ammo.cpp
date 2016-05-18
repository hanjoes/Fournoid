// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Characters/PlayerCharacter.h"
#include "Weapons/FournoidWeapon.h"
#include "FournoidPickup_Ammo.h"

AFournoidPickup_Ammo::AFournoidPickup_Ammo(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer){
	AmmoClips = 2;
}

bool AFournoidPickup_Ammo::CanBePickedUp(AFournoidCharacter *TestPawn)const{
	if(TestPawn->IsA<APlayerCharacter>()){
		AFournoidWeapon* CurrWeapon = TestPawn->GetWeaponActor();
		//if(CurrWeapon->)
	}
	return true;
}

bool AFournoidPickup_Ammo::IsForWeapon(UClass* WeaponClass){
	return false;
}

void AFournoidPickup_Ammo::GivePickupTo(AFournoidCharacter* Pawn){
	FournoidUtils::GreenMessage("Trying to give To Pawn");
	if( Pawn->IsA<APlayerCharacter>() ){
		FournoidUtils::BlueMessage("Ennn, Player");
		AFournoidWeapon* Weapon = Pawn->GetWeaponActor();
		if(Weapon){
			FournoidUtils::GreenMessage("Giving To Pawn");
			Weapon->AddCurrentStore(AmmoClips*30);
		}
	}
}


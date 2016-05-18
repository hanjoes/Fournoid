// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "Characters/PlayerCharacter.h"
#include "FournoidPickup_Health.h"

AFournoidPickup_Health::AFournoidPickup_Health(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Health = 50;
}

void AFournoidPickup_Health::GivePickupTo(AFournoidCharacter *Pawn)
{
	if ( Pawn )
	{
		Pawn->SetHealth(FMath::Min(FMath::TruncToInt(Pawn->GetCharacterHealth()) + Health, 100));
	}
}

bool AFournoidPickup_Health::CanBePickedUp(AFournoidCharacter *TestPawn) const
{
	if ( TestPawn->IsA<APlayerCharacter>() )
	{
		if ( TestPawn->GetCharacterHealth() < 100.f )
		{
			return true;
		}
	}
	return false;
}


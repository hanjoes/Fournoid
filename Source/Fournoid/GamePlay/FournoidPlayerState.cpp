// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidPlayerState.h"

AFournoidPlayerState::AFournoidPlayerState()
{
	// Default values
	NumDeath = 0;
	NumKills = 0;
}

void AFournoidPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME(AFournoidPlayerState, NumDeath);
	DOREPLIFETIME(AFournoidPlayerState, NumKills);
}

void AFournoidPlayerState::ScoreKill()
{
	NumKills += 1;
}

void AFournoidPlayerState::ScoreDeath()
{
	NumDeath += 1;
}


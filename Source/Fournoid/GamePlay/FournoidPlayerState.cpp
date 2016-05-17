// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidPlayerState.h"

AFournoidPlayerState::AFournoidPlayerState()
{
	// Default values
	NumDeaths = 0;
	NumKills = 0;
}

void AFournoidPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME(AFournoidPlayerState, NumDeaths);
	DOREPLIFETIME(AFournoidPlayerState, NumKills);
}

void AFournoidPlayerState::ScoreKill()
{
	NumKills += 1;
}

void AFournoidPlayerState::ScoreDeath()
{
	NumDeaths += 1;
}

int32 AFournoidPlayerState::GetNumKills() const
{
	return NumKills;
}

int32 AFournoidPlayerState::GetNumDeaths() const
{
	return NumDeaths;
}



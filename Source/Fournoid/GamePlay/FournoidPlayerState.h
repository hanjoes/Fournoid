// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "FournoidPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	AFournoidPlayerState();
	
	//////////////////////////////////////////////////////////////////////////
	// Scoring
	
public:
	
	/** Add one to NumKills */
	void ScoreKill();
	
	/** Add one to NumDeath */
	void ScoreDeath();
	
	/** Getter for NumKills */
	int32 GetNumKills() const;
	
	/** Getter for NumDeaths */
	int32 GetNumDeaths() const;
	
	
protected:
	
	UPROPERTY(Replicated)
	int32 NumDeaths;
	
	UPROPERTY(Replicated)
	int32 NumKills;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "FournoidGameState.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidGameState : public AGameState
{
	GENERATED_BODY()
	
	
public:
	
	void LogCurrentGameScore() const;
	
	
};

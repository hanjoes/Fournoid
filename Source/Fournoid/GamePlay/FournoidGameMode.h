// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "FournoidGameMode.generated.h"

namespace GameModeConstants
{
	const float REASONABLE_DISTANCE = 1000.f;
}

UCLASS(minimalapi)
class AFournoidGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	AFournoidGameMode();
	
	/** Called when a character kills another */
	void Killed(AController* Killer, AController* Killed);
	
	/** overriden the behavior to choose the best spawn point */
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
protected:
	
	virtual bool IsPlayerStartReasonable(APlayerStart* TestSpawn);
};




// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "FournoidGameMode.generated.h"

UCLASS(minimalapi)
class AFournoidGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	AFournoidGameMode();
	
	void Killed(AController* Killer, AController* Killed);
};




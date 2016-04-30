// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidGameMode.h"
#include "FournoidHUD.h"
#include "FournoidCharacter.h"

AFournoidGameMode::AFournoidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFournoidHUD::StaticClass();
}

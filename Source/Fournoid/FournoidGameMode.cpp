// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "Characters/FournoidPlayerController.h"
#include "FournoidGameMode.h"
#include "FournoidGameState.h"
#include "FournoidHUD.h"

AFournoidGameMode::AFournoidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/FournoidAssets/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawn.Class;
	PlayerControllerClass = AFournoidPlayerController::StaticClass();
	GameStateClass = AFournoidGameState::StaticClass();

	// HUD class
	static ConstructorHelpers::FClassFinder<AHUD> TheHUDOb(TEXT("/Game/UserInterface/MyFournoidHUD.MyFournoidHUD_C"));
	if (TheHUDOb.Class != NULL)
	{
		HUDClass = TheHUDOb.Class;
	}
	
	// default values for FournoidGameMode
	MinRespawnDelay = 4.f;
}

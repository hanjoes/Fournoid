// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "Characters/FournoidPlayerController.h"
#include "FournoidGameMode.h"
#include "FournoidHUD.h"

AFournoidGameMode::AFournoidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/FournoidAssets/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawn.Class;
	PlayerControllerClass = AFournoidPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = AFournoidHUD::StaticClass();
}

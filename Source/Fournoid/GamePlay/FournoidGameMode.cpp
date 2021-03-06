// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "Characters/FournoidPlayerController.h"
#include "FournoidGameState.h"
#include "FournoidGameMode.h"
#include "FournoidPlayerState.h"
#include "FournoidGameState.h"
#include "FournoidHUD.h"

AFournoidGameMode::AFournoidGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawn(TEXT("/Game/FournoidAssets/Blueprints/PlayerCharacter_BP"));
	DefaultPawnClass = PlayerPawn.Class;
	PlayerStateClass = AFournoidPlayerState::StaticClass();
	GameStateClass = AFournoidGameState::StaticClass();

	// Player Controller class
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerOb(TEXT("/Game/FournoidAssets/Blueprints/FournoidPlyaerController_BP"));
	if (PlayerControllerOb.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerOb.Class;
	}

	// HUD class
	static ConstructorHelpers::FClassFinder<AHUD> TheHUDOb(TEXT("/Game/UserInterface/MyFournoidHUD.MyFournoidHUD_C"));
	if (TheHUDOb.Class != NULL)
	{
		HUDClass = TheHUDOb.Class;
	}
	
	// default values for FournoidGameMode
	MinRespawnDelay = 4.f;
}

void AFournoidGameMode::Killed(AController *Killer, AController *Killed)
{
	// For some reason one of Killed and Killer could be nullptr and the method is passed twice.
	auto KillerPlayerState = Killer ? Cast<AFournoidPlayerState>(Killer->PlayerState) : nullptr;
	auto KilledPlayerState = Killed ? Cast<AFournoidPlayerState>(Killed->PlayerState) : nullptr;
	
	if ( Killer && KillerPlayerState && KillerPlayerState != KilledPlayerState )
	{
		KillerPlayerState->ScoreKill();
	}
	
	if ( Killed && KilledPlayerState && KilledPlayerState != KillerPlayerState )
	{
		KilledPlayerState->ScoreDeath();
	}
}

AActor* AFournoidGameMode::ChoosePlayerStart_Implementation(AController *Player)
{
	UE_LOG(Fournoid, Warning, TEXT("Choosing player start..."));
	TArray<APlayerStart*> ReasonablePlayerStarts;
	
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		auto TestSpawn = *It;
		
		if ( IsPlayerStartReasonable(TestSpawn ))
		{
			ReasonablePlayerStarts.Add(TestSpawn);
		}
	}
	
	int32 ResultNum = ReasonablePlayerStarts.Num();
	if ( ResultNum > 0 )
	{
		return ReasonablePlayerStarts[FMath::RandHelper(ResultNum)];
	}
	
	// Regress to parent class implementation
	return Super::ChoosePlayerStart_Implementation(Player);
}

bool AFournoidGameMode::IsPlayerStartReasonable(APlayerStart *TestSpawn)
{
	for (TActorIterator<AFournoidCharacter> It(GetWorld()); It; ++It)
	{
		auto CurrentPawn = *It;
		
		if ( CurrentPawn->GetDistanceTo(TestSpawn) < GameModeConstants::REASONABLE_DISTANCE )
		{
			return false;
		}
	}
	return true;
}

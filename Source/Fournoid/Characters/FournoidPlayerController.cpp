// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidPlayerController.h"


void AFournoidPlayerController::Suicide()
{
	auto Character = Cast<AFournoidCharacter>(GetPawn());
	if ( Character )
	{
		Character->Die(this);
	}
}

void AFournoidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// UI input
	InputComponent->BindAction("Scoreboard", IE_Pressed, this, &AFournoidPlayerController::ShowScoreboard);
	InputComponent->BindAction("Scoreboard", IE_Released, this, &AFournoidPlayerController::HideScoreboard);
}

void AFournoidPlayerController::PawnPendingDestroy(APawn* P)
{
	auto DeathLocation = P->GetActorLocation();
	FVector CameraLocation = DeathLocation + FVector(0, 0, 300.0f);
	FRotator CameraRotation(-90.0f, 0.0f, 0.0f);

	Super::PawnPendingDestroy(P);

	ClientSetSpectatorCamera(CameraLocation, CameraRotation);
}

void AFournoidPlayerController::ClientSetSpectatorCamera_Implementation(FVector CameraLocation, FRotator CameraRotation)
{
	SetInitialLocationAndRotation(CameraLocation, CameraRotation);
	SetViewTarget(this);
}

void AFournoidPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AFournoidPlayerController::ShowScoreboard()
{
	auto World = GetWorld();
	if ( World )
	{
		auto GameState = World->GetGameState<AFournoidGameState>();
		GameState->LogCurrentGameScore();
	}
}

void AFournoidPlayerController::HideScoreboard()
{
	
}
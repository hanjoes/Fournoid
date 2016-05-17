// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "FournoidPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API AFournoidPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	//////////////////////////////////////////////////////////////////////////
	// Console Commands
	
public:
	
	/** Issued by the player to kill the character possessed */
	UFUNCTION(Exec)
	void Suicide();
	
	//////////////////////////////////////////////////////////////////////////
	// Camera Related
	
	/** update camera when pawn dies */
	virtual void PawnPendingDestroy(APawn* P) override;
	
	/** sets spectator location and rotation */
	UFUNCTION(reliable, client)
	void ClientSetSpectatorCamera(FVector CameraLocation, FRotator CameraRotation);
	
	//////////////////////////////////////////////////////////////////////////
	// Spawn
	
	virtual void UnFreeze() override;
	
};

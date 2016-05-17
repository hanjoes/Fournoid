// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidGameInstance.h"


namespace FournoidGameInstanceState
{
	const FName None = FName(TEXT("None"));
	const FName PendingInvite = FName(TEXT("PendingInvite"));
	const FName WelcomeScreen = FName(TEXT("WelcomeScreen"));
	const FName MainMenu = FName(TEXT("MainMenu"));
	const FName MessageMenu = FName(TEXT("MessageMenu"));
	const FName Playing = FName(TEXT("Playing"));
}


UFournoidGameInstance::UFournoidGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentState = FournoidGameInstanceState::None;
}

void UFournoidGameInstance::Init()
{
	Super::Init();
	
}

void UFournoidGameInstance::StartGameInstance()
{
	Super::StartGameInstance();
}

void UFournoidGameInstance::Shutdown()
{
	Super::Shutdown();
	
}

bool UFournoidGameInstance::StartPIEGameInstance(ULocalPlayer *LocalPlayer, bool bInSimulateInEditor, bool bAnyBlueprintErrors, bool bStartInSpectatorMode)
{
	bool result = Super::StartPIEGameInstance(LocalPlayer, bInSimulateInEditor, bAnyBlueprintErrors, bStartInSpectatorMode);
	StartGameInstance();
	return result;
}


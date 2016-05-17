// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "FournoidGameInstance.generated.h"

namespace FournoidGameInstanceState
{
	extern const FName None;
	extern const FName PendingInvite;
	extern const FName WelcomeScreen;
	extern const FName MainMenu;
	extern const FName MessageMenu;
	extern const FName Playing;
}

/**
 * 
 */
UCLASS(config=Game)
class FOURNOID_API UFournoidGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void Init() override;
	
	virtual void Shutdown() override;
	
	virtual void StartGameInstance() override;
	
private:
	
	UPROPERTY(Config)
	FString EntryMap;
	
	FName CurrentState;
	
};

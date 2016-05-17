// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "FournoidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API UFournoidGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	virtual void Init() override;
	
	virtual void Shutdown() override;
	
	virtual void StartGameInstance() override;
	
};

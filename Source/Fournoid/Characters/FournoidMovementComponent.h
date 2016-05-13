// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "FournoidMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FOURNOID_API UFournoidMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	virtual float GetMaxSpeed() const override;
	
};

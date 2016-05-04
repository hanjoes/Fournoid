// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidCharacter.h"
#include "Assists/FournoidAssist.h"
#include "FournoidProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AFournoidCharacter::AFournoidCharacter()
: Health(100.0f), Stamina(100.0f), StaminaRegenRate(15.f), StaminaConsumeRate(30.f), SpeedBoostScale(1.5f), bCharacterIsRunning(false)
{
    Assist = CreateDefaultSubobject<AFournoidAssist>("StartAssist");
    Assist->AttachRootComponentTo(RootComponent);
}

void AFournoidCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFournoidCharacter::ReceiveDamage(float Damage)
{
	Health -= Damage;
}

void AFournoidCharacter::SetSpeedBoostScale(float NewScale)
{
	SpeedBoostScale = NewScale;
}

void AFournoidCharacter::StartRunning()
{
	GetCharacterMovement()->MaxWalkSpeed *= SpeedBoostScale;
	bCharacterIsRunning = true;
}

void AFournoidCharacter::StopRunning()
{
	// Lower movement speed if character is running.
	if (bCharacterIsRunning) {
    	GetCharacterMovement()->MaxWalkSpeed /= SpeedBoostScale;
    	bCharacterIsRunning = false;
	}
}

void AFournoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
    if (bCharacterIsRunning && (GetVelocity() != FVector::ZeroVector)) {
		Stamina -= DeltaTime * StaminaConsumeRate;
		
		// If stamina is equal or below zero, stop running.
		if (Stamina <= 0.0f) {
			StopRunning();
		}
	}
	else {
		// regen only if stamina is not full
		if (Stamina < 100.f) {
    		Stamina += DeltaTime * StaminaRegenRate;
			Stamina = FMath::Min(Stamina, 100.f);
		}
	}
}

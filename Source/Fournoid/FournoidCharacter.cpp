// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidCharacter.h"
#include "FournoidProjectile.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AFournoidCharacter::AFournoidCharacter()
: Health(100.0f), SpeedBoostScale(1.5f)
{
}

void AFournoidCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AFournoidCharacter::ReceiveDamage(float Damage)
{
	Health -= Damage;
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 2, FColor::Red, FString::Printf(TEXT("%s received %f damage, %f health left."), *GetName(), Damage, Health));
}

void AFournoidCharacter::SetSpeedBoostScale(float NewScale)
{
	SpeedBoostScale = NewScale;
}

void AFournoidCharacter::StartRunning()
{
	GetCharacterMovement()->MaxWalkSpeed *= SpeedBoostScale;
	
}

void AFournoidCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed /= SpeedBoostScale;
}
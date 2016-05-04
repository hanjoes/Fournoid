// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Damageable.h"
#include "GameFramework/Character.h"
#include "FournoidCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AFournoidCharacter : public ACharacter, public IDamageable
{
	GENERATED_BODY()
public:
	AFournoidCharacter();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	FORCEINLINE float GetCharacterHealth() const { return Health; }
	
	FORCEINLINE float GetCharacterStamina() const { return Stamina; }
	
	FORCEINLINE float GetStaminaRegenRate() const { return StaminaRegenRate; }
	
	FORCEINLINE float GetStaminaConsumeRate() const { return StaminaConsumeRate; }
	
	FORCEINLINE float GetSpeedScale() const { return Stamina; }
	
	FORCEINLINE bool CharacterIsRunning() const { return bCharacterIsRunning; }
	
	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetSpeedBoostScale(float SpeedBoostScale);
	
	void StartRunning();
	
	void StopRunning();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	float Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	float Stamina;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	float StaminaRegenRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	float StaminaConsumeRate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	float SpeedBoostScale;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
	bool bCharacterIsRunning;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
    class AFournoidAssist* Assist;
	
	/////////////////////////////////////////////////
	// IDamageable
public:
	void ReceiveDamage(float Damage) override;
};


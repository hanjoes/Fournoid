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
	
	FORCEINLINE float GetCharacterHealth() const { return Health; }
	
	FORCEINLINE float GetCharacterStamina() const { return Stamina; }
	
	FORCEINLINE float GetSpeedScale() const { return Stamina; }
	
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
	float SpeedBoostScale;
	
	/////////////////////////////////////////////////
	// IDamageable
public:
	void ReceiveDamage(float Damage) override;
};


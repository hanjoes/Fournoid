// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "FournoidCharacter.generated.h"

class UInputComponent;

UCLASS(config=Game)
class AFournoidCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AFournoidCharacter();
	
	virtual void BeginPlay() override;
    
    FORCEINLINE float GetCharacterHealth() const { return Health; }
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Character")
    float Health;
};


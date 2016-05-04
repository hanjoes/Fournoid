// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interface.h"
#include "Damageable.generated.h"

UINTERFACE(Blueprintable)
class FOURNOID_API UDamageable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageable
{
	GENERATED_IINTERFACE_BODY()
public:
	virtual void ReceiveDamage(float Damage) = 0;
};

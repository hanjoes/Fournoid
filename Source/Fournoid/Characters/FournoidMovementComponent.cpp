// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidMovementComponent.h"


float UFournoidMovementComponent::GetMaxSpeed() const
{
	float Speed = Super::GetMaxSpeed();
	auto Character = Cast<AFournoidCharacter>(GetPawnOwner());
	if ( Character )
	{
		if ( Character->CharacterIsRunning() )
		{
			auto OldSpeed = Speed;
    		Speed *= Character->GetSpeedScale();
		}
	}
	return Speed;
}
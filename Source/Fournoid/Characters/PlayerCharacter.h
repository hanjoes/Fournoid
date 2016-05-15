// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FournoidCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FOURNOID_API APlayerCharacter : public AFournoidCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	void PlayHitSound();
	
	/** Plays when a damage caused by this player is confirmed */
	UFUNCTION(Reliable, Client)
	void ClientPlayHitSound();
	
	/////////////////////////////////////////////////
	// Controll
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);
	
	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	
	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;
	
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	/////////////////////////////////////////////////
	// Keeper
	
protected:
	
	void SpawnKeeper() override;
	
	// TODO: This is for keeper not bullet.
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector SpawnOffset;
	
	/////////////////////////////////////////////////
	// APawn
	
protected:
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	/////////////////////////////////////////////////
	// Components
	
protected:
	
	/** First person camera */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FirstPersonCameraComponent;
	
	/** Plays a hit sound when this pawn's weapon hit a pawn. */
	UPROPERTY(EditAnyWhere, Category=Audio)
	USoundBase* HitSound;
	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};

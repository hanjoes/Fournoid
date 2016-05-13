// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FournoidCharacter.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FOURNOID_API APlayerCharacter : public AFournoidCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	APlayerCharacter(const FObjectInitializer& ObjectInitializer);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowProtectedAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
	
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	
};

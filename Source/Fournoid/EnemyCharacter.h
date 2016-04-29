// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FOURNOID_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    /** Return the skeletal mesh of the enemy */
    FORCEINLINE USkeletalMeshComponent* GetEnemyMesh() const { return EnemyMesh; }

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Enemy")
    USkeletalMeshComponent* EnemyMesh;
};

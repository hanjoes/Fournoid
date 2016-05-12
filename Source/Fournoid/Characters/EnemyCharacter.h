// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FournoidCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FOURNOID_API AEnemyCharacter : public AFournoidCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	//Behavior Tree
	UPROPERTY(EditAnywhere, Category= Behavior)
	class UBehaviorTree *BotBehavior;
	
	UPROPERTY(EditDefaultsOnly, Category=Bullet)
	TSubclassOf<class AFournoidBullet> BulletClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector SpawnOffset;
	
	/////////////////////////////////////////////////
	// IDamageable
public:
	void SetPatrolLoc(FVector Location);
	FVector GetPatrolLoc();
	
	TQueue<FVector> *GetEnemyLocs();
	
	void ReceiveDamage(float Damage) override;
	
	void OnFire();
	
private:
	void SetupCollisionBehavior();
	
	TQueue<FVector> EnemyLocations;
	
	FVector PatrolLocation;
};

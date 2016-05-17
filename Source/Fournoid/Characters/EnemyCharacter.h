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
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	//Behavior Tree
	UPROPERTY(EditAnywhere, Category= Behavior)
	class UBehaviorTree *BotBehavior;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector SpawnOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float PatrolRadius = 800.f;
	
	bool IsFirstPerson() const override;
	
public:
	
	float GetPatrolRadius();
	
	void StartFire();
	
	void StopFire();
	
	//Check CurrentStore if less than or equal to 0, reload the storage
	int32 ReloadStore();
	
private:
	void SetupCollisionBehavior();
};

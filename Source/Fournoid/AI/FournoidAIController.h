// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "FournoidAIController.generated.h"

/**
 *
 */
UCLASS()
class FOURNOID_API AFournoidAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(transient)
	class UBlackboardComponent *BlackboardComp;
	
	UPROPERTY(transient)
	class UBehaviorTreeComponent *BehaviorComp;
	
	enum AIState{
		IDLE,
		COMBAT
	};
	
public:
	
	AFournoidAIController();
	
	virtual void Possess(APawn *InPawn) override;
	
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void FindClosestEnemy();
	
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void ShootEnemy();
	
	//Aim at enemy
	//virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;
	
	void SetEnemy(APawn *Inpawn);
	class AFournoidCharacter* GetEnemy();
	
	uint8 EnemyKeyID;
	
};
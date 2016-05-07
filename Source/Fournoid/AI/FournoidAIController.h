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
	
public:
	
	AFournoidAIController();
	
	virtual void Possess(APawn *InPawn) override;
	
	uint8 EnemyKeyID;
	
};
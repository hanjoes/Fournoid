// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "EnemyCharacter.h"
#include "FournoidAIController.h"

AFournoidAIController::AFournoidAIController(){
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	
}

void AFournoidAIController::Possess(APawn *InPawn){
	Super::Possess(InPawn);
	
	AEnemyCharacter *Enemy = Cast<AEnemyCharacter>(InPawn);
	
	if(Enemy && Enemy->BotBehavior){
		BlackboardComp ->InitializeBlackboard(*Enemy->BotBehavior->BlackboardAsset);
		
		EnemyKeyID = BlackboardComp->GetKeyID("Target");
		
		BehaviorComp ->StartTree(*Enemy->BotBehavior);
		
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Behavior");
	}
	
}



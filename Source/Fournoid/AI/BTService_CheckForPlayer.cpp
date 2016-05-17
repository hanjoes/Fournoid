// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Characters/FournoidCharacter.h"
#include "FournoidAIController.h"
#include "Characters/EnemyCharacter.h"
#include "BTService_CheckForPlayer.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer(){
	bCreateNodeInstance = true;
	
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	AFournoidAIController *CharPC = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	
	if(CharPC){
		
		CharPC->FindClosestEnemy();
		CharPC->ShootEnemy();
	}
}

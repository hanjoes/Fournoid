// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FournoidAIController.h"
#include "Characters/FournoidCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "BTTask_MoveToPlayer.h"

EBTNodeResult::Type
UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	AFournoidAIController *EnemyPC = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	
	AFournoidCharacter *Enemy = Cast<AFournoidCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID));
	
	if(Enemy){
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
	
}

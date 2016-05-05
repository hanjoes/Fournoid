// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FournoidAIController.h"
#include "FournoidCharacter.h"
#include "EnemyCharacter.h"
#include "BTTask_MoveToPlayer.h"

EBTNodeResult::Type
UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){
	AFournoidAIController *EnemyPC = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	
	AFournoidCharacter *Enemy = Cast<AFournoidCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID));
	
	if(Enemy){
//		EnemyPC->MoveToActor(Enemy,5.f,true,true,true, 0,true);
//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Moving to player");
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
	
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FournoidCharacter.h"
#include "FournoidAIController.h"
#include "EnemyCharacter.h"
#include "BTService_CheckForPlayer.h"

UBTService_CheckForPlayer::UBTService_CheckForPlayer(){
	bCreateNodeInstance = true;
	
}

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	AFournoidAIController *EnemyPC = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	
	if(EnemyPC){
		AFournoidCharacter *Enemy = Cast<AFournoidCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		
		if(Enemy){
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyPC->EnemyKeyID,Enemy);
			
			EnemyPC->MoveToActor(Enemy,5.f,true,true,true,0,true);
			//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "I'm an Enemy");
		}
	}
}


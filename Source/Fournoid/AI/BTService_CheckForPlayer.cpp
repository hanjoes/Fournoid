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
		AFournoidCharacter *Enemy =Cast<AFournoidCharacter>( OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(CharPC->EnemyKeyID)) ;
		
		if(Enemy){

			FVector AILocation = CharPC->AActor::GetActorLocation();
			FVector EnemyLocation = Enemy->GetActorLocation();
			FVector Direction = UKismetMathLibrary::Normal(EnemyLocation-AILocation);
			FVector CharForward = CharPC->GetActorForwardVector();
			
			float Angel = UKismetMathLibrary::DegAcos(UKismetMathLibrary::Dot_VectorVector(Direction, CharForward));
			
			float Distance =sqrt( (EnemyLocation-AILocation).SizeSquared());
			FournoidUtils::BlueMessage(FString::SanitizeFloat(Angel)+","+FString::SanitizeFloat(Distance));
			
			if( Angel<60 && Distance <2000){
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("AIState", 1);
				OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", Enemy);
				
			}else{
				CharPC->ClearFocus(EAIFocusPriority::Gameplay);

				OwnerComp.GetBlackboardComponent()->SetValueAsEnum("AIState", 0);
			}
		}
	}
}


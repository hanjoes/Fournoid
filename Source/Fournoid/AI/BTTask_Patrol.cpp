// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FournoidAIController.h"
#include "Characters/FournoidCharacter.h"
#include "Characters/EnemyCharacter.h"
#include "BTTask_Patrol.h"


EBTNodeResult::Type
UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory){

	AFournoidAIController* MyController = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	APawn* MyWaypoint = MyController->GetPawn();
	if (MyWaypoint)
	{
		/* Find a position that is close to the waypoint. We add a small random to this position to give build predictable patrol patterns  */
		const float SearchRadius = 800.0f;
		const FVector SearchOrigin = MyWaypoint->GetActorLocation();
		const FVector Loc = UNavigationSystem::GetRandomPointInNavigableRadius(MyController, SearchOrigin, SearchRadius);
		
		float speed = Cast<AEnemyCharacter>(MyController->GetCharacter())->GetCharacterMovement()->MaxWalkSpeed = 300;
		//FournoidUtils::GreenMessage(FString::SanitizeFloat(speed));
		if (Loc != FVector::ZeroVector)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
			
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	
	return EBTNodeResult::Failed;
}


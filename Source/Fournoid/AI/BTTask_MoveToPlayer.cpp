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
	AFournoidAIController *MyController = Cast<AFournoidAIController>(OwnerComp.GetAIOwner());
	AEnemyCharacter *Bot = Cast<AEnemyCharacter>(MyController->GetCharacter());
	AFournoidCharacter *Enemy = MyController->GetEnemy();
	
	if(Enemy && Bot){
		Cast<AEnemyCharacter>(MyController->GetCharacter())->GetCharacterMovement()->MaxWalkSpeed = 500;
		MyController->SetFocus(Enemy);
		FVector Loc;
		if(Bot->GetPatrolRadius() > 0.f){
			const float SearchRadius = 200.f;
			const FVector SearchOrigin = Enemy->GetActorLocation() + 200.0f * (Bot->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
			Loc = UNavigationSystem::GetRandomReachablePointInRadius(MyController, SearchOrigin, SearchRadius);
		}else{
			Loc = MyController->AActor::GetActorLocation();
			
		}
		if(Loc != FVector::ZeroVector){
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(),Loc);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
	
}
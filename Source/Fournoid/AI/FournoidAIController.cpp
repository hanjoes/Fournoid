#include "Fournoid.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Characters/EnemyCharacter.h"
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
	}
	
}

void AFournoidAIController::ShootEnemy(){
	AEnemyCharacter* MyBot = Cast<AEnemyCharacter>(GetPawn());
	//AShooterWeapon* MyWeapon = MyBot ? MyBot->GetWeapon() : NULL;
	
	bool bCanShoot = false;
	AFournoidCharacter* Enemy = GetEnemy();
	if ( MyBot->IsAlive() && Enemy && ( Enemy->IsAlive() ))
	{
		if (LineOfSightTo(Enemy, MyBot->GetActorLocation()))
		{
			bCanShoot = true;
		}
	}
	
	if (bCanShoot)
	{
		MyBot->StartFire();
	}
	else
	{
		MyBot->StopFire();
	}
}

void AFournoidAIController::FindClosestEnemy(){
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}
	
	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AFournoidCharacter* BestPawn = NULL;
	
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AFournoidCharacter* TestPawn = Cast<AFournoidCharacter>(*It);
		if (TestPawn && TestPawn->IsAlive() && TestPawn->GetController()->IsA(APlayerController::StaticClass()))
		{
			const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
			if (DistSq < BestDistSq &&  sqrt(DistSq) < 2500.f )
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}
	
	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}else {
		SetEnemy(NULL);
	}
}

void AFournoidAIController::SetEnemy(APawn *InPawn){
	if(BlackboardComp){
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		if(InPawn!=NULL){
			SetFocus(InPawn);
		}else{
			ClearFocus(EAIFocusPriority::Gameplay);
		}
	}
}

class AFournoidCharacter* AFournoidAIController::GetEnemy(){
	if(BlackboardComp){
		return Cast<AFournoidCharacter>( BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}
	return NULL;
}

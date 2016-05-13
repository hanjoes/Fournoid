// Fill out your copyright notice in the Description page of Project Settings.

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
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, "Shooting!");

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
		if (TestPawn && !TestPawn->IsDead() && TestPawn->GetController()->IsA(APlayerController::StaticClass()))
		{
			const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
			if (DistSq < BestDistSq)
			{
				//FournoidUtils::BlueMessage( FString::SanitizeFloat( sqrt(DistSq) ) );
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}
	
	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
}

void AFournoidAIController::SetEnemy(APawn *InPawn){
	if(BlackboardComp){
		BlackboardComp->SetValueAsObject("Target", InPawn);
		//FournoidUtils::BlueMessage("Set");
	}
}

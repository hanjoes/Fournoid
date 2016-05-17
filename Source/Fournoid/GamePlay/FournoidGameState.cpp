// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidGameState.h"


void AFournoidGameState::LogCurrentGameScore() const
{
	TMap<FString, TPair<int32, int32>> ScoreMap;
	for (auto RawPlayerState : PlayerArray)
	{
		auto PlayerState = Cast<AFournoidPlayerState>(RawPlayerState);
		if ( PlayerState )
		{
			TPairInitializer<int32, int32> initializer(PlayerState->GetNumKills(), PlayerState->GetNumDeaths());
    		ScoreMap.Add(PlayerState->GetName(), TPair<int32, int32>(initializer));
		}
	}
	ScoreMap.ValueSort([](TPair<int32, int32> PairA, TPair<int32, int32> PairB){ return PairA.Key > PairB.Key; });
	
	UE_LOG(Fournoid, Warning, TEXT("------------------------"));
	for (auto It = ScoreMap.CreateConstIterator(); It; ++It)
	{
		UE_LOG(Fournoid, Warning, TEXT("Player: %s\tKills: %d\tDeaths:%d"), *(It.Key()), It.Value().Key, It.Value().Value);
	}
}
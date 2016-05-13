// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class FOURNOID_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	// Accessors
	FORCEINLINE UBoxComponent* GetSpawnBox() const { return SpawnBox; }
	
	// Returns a random point in the volume
	UFUNCTION(BluePrintPure, Category = "Spawning")
	FVector GetRandomPointInVolume() const;
	
	// Spawn an enemy into the world
	UFUNCTION(BluePrintCallable, Category = "Spawning")
	void SpawnEnemy();
	
protected:
	UPROPERTY(EditAnywhere, Category = "Spawing")
	TSubclassOf<class AEnemyCharacter> EnemyToSpawn;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
	int MaxEnenyNum;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning")
	float SpawnIntervalRangeLo;
	
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Spawning")
	float SpawnIntervalRangeHi;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Spawning")
	float SpawnInterval;
	
protected:
	void registerTimer();
	
private:
	// The place from where the enemy will be spawned.
	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *SpawnBox;
	
	FTimerHandle SpawnTimer;
	
	unsigned EnemySpawned;
};

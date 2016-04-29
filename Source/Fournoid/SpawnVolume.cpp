// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "SpawnVolume.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize the spawn component.
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = SpawnBox;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnVolume::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector origin = SpawnBox->Bounds.Origin;
	FVector extent = SpawnBox->Bounds.BoxExtent;
	
	return UKismetMathLibrary::RandomPointInBoundingBox(origin, extent);
}

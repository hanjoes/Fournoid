// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidKeeper.h"


// Sets default values
AFournoidKeeper::AFournoidKeeper()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeeperMesh"));
	RootComponent = StaticMeshComp;
}

// Called when the game starts or when spawned
void AFournoidKeeper::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFournoidKeeper::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AFournoidKeeper::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


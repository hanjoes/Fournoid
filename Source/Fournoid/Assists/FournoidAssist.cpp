// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidAssist.h"


// Sets default values
AFournoidAssist::AFournoidAssist()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>("AssistMeshComponent");
    RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AFournoidAssist::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFournoidAssist::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AFournoidAssist::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}


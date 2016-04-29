// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Create the mesh component that is associated with enemy character.
    EnemyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnemyCharacter"));
    EnemyMesh->SetOnlyOwnerSee(true);
    EnemyMesh->bCastDynamicShadow = false;
    EnemyMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


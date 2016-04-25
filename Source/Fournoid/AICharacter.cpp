// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "AICharacter.h"


// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

//Step 1: Implement the CalculateHealth function.
void AAICharacter::CalculateHealth(float Delta)
{
	Health += Delta;
	CalculateDead();
}

//Step 2: Implement the CalculateDead function.
void AAICharacter::CalculateDead()
{
	if (Health <= 0)
		isDead = true;
	else
		isDead = false;

}
#if WITH_EDITOR
//Step 3: Implement the remainder of our helper code, used by the editor when we change values.
void AAICharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	isDead = false;
	Health = 100;
	Super::PostEditChangeProperty(PropertyChangedEvent);

	CalculateDead();
}
#endif

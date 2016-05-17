// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "PlayerCharacter.h"
#include "Bullets/FournoidBullet.h"
#include "Keepers/FournoidKeeper.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/InputSettings.h"

APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	
	// Setup default values
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
//	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

//////////////////////////////////////////////////////////////////////////
// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);
	
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	InputComponent->BindAction("Run", IE_Pressed, this, &AFournoidCharacter::StartRunning);
	InputComponent->BindAction("Run", IE_Released, this, &AFournoidCharacter::StopRunning);
	
	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	InputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::StartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);
	
	InputComponent->BindAction("Reload", IE_Pressed, this, &AFournoidCharacter::ReloadCurrentWeapon);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::SpawnKeeper()
{
	if (Role < ROLE_Authority)
	{
		return;
	}
	
	// try and fire a projectile
	if (KeeperClass)
	{
		FournoidUtils::BlueMessage(TEXT("Spwaning Keeper"));
		// Get the actors rotation caused by control in world space.
		const FRotator SpawnRotation = GetControlRotation();
		// Tarnsform the SpawnOffset from local space to world space.
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(SpawnOffset);
		
		UWorld* const World = GetWorld();
		if (World)
		{
			FournoidUtils::BlueMessage(TEXT("Spwaning..."));
			// spawn the projectile at the muzzle
			auto SpawnedKeeper = World->SpawnActor<AFournoidKeeper>(KeeperClass, SpawnLocation, SpawnRotation);
			SpawnedKeeper->SetKeeperMaster(this);
		}
	}
}

void APlayerCharacter::PlayHitSound()
{
	if ( HitSound && IsLocallyControlled() )
	{
		UGameplayStatics::SpawnSoundAttached(HitSound, Mesh1P);
	}
}

void APlayerCharacter::ClientPlayHitSound_Implementation()
{
	PlayHitSound();
}

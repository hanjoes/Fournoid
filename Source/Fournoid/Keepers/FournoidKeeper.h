// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FournoidKeeper.generated.h"

UCLASS()
class FOURNOID_API AFournoidKeeper : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFournoidKeeper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category=Keeper)
	UStaticMeshComponent* StaticMeshComp;
	
};

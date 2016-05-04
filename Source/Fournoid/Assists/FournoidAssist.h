// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "FournoidAssist.generated.h"

UCLASS()
class FOURNOID_API AFournoidAssist : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFournoidAssist();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

protected:
    UPROPERTY(VisibleAnywhere, meta = (AllowProtectedAccess = "true"))
    UStaticMeshComponent* Mesh;
	
};

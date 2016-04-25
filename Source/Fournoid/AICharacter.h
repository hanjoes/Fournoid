// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AICharacter.generated.h"

UCLASS(Blueprintable)
class FOURNOID_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Step 2: Expose a float property
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AICharacter")
		float Health = 100;

	//Step 3: Expose a boolean property
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AICharacter")
		bool isDead = false;


	//Step 4: Make a helper function, just because we are lazy
	virtual void CalculateDead();

	//Step 5: Expose a method
	UFUNCTION(BlueprintCallable, Category = "AICharacter")
		virtual void CalculateHealth(float delta);


	//Step 6: Editor code to make updating values in the editor cleaner
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif


	// Sets default values for this character's properties
	AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};

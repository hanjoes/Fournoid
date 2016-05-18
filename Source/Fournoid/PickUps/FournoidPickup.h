// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidPickup.generated.h"

UCLASS()
class FOURNOID_API AFournoidPickup : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AFournoidPickup(const FObjectInitializer& ObjectInitializer);

	/** pickup on touch */
	virtual void NotifyActorBeginOverlap(class AActor* Other) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	//if this pickup can be pick up
	virtual bool CanBePickedUp(AFournoidCharacter* TestPawn) const;
	
protected:
	
	/** Handle for efficient management of RespawnPickup timer */
	FTimerHandle TimerHandle_RespawnPickup;

	virtual void GivePickupTo(AFournoidCharacter* Pawn);
	
	virtual void Respawn();
	/** show effects when pickup appears */
	virtual void OnRespawned();
	
	/** handle touches */
	void PickupOnTouch(class AFournoidCharacter* Pawn);

	/** show effects when pickup disappears */
	virtual void OnPickedUp();
	
private:
	/** FX component */
	UPROPERTY(VisibleDefaultsOnly, Category=Effects)
	UParticleSystemComponent* PickupPSC;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=Effects)
	UParticleSystem* ActiveFX;
	
	UPROPERTY(EditDefaultsOnly, Category=Pickup)
	float RespawnTime;
	
	/** is it ready for interactions? */
	//UPROPERTY(Transient, ReplicatedUsing=OnRep_IsActive)
	UPROPERTY(transient)
	uint32 bIsActive:1;
	
	/** Returns PickupPSC subobject */
	FORCEINLINE UParticleSystemComponent* GetPickupPSC() const { return PickupPSC; }
	
};

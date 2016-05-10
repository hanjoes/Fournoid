// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidWeapon.generated.h"

UCLASS(Abstract, BluePrintable)
class FOURNOID_API AFournoidWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFournoidWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	
	void SetOwningPawn( class AFournoidCharacter* OwningChara );
	
	//////////////////////////////////////////////////////////////////////////
	// Inventory
public:
	virtual void OnEquip();
	
	virtual void OnUnEquip();
	
	virtual void OnEnterInventory(class AFournoidCharacter* OwnerChara);
	
	void AttachWeaponToPawn();
	
	void DetachWeaponFromPawn();
	
	UPROPERTY(Transient)
	class AFournoidCharacter* MyPawn;
	
private:
	/** Mesh for 1st person perspective */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;
	
	/** Mesh for 3st person perspective */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh3P;
	
};

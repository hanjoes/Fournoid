// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "FournoidOrbiter.generated.h"

UCLASS()
class FOURNOID_API AFournoidOrbiter : public AActor
{
	GENERATED_BODY()
	
public:
	
	AFournoidOrbiter();
	
	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	/** The parent of this orbiter */
	UPROPERTY(EditAnywhere, Category=Parent)
	AFournoidOrbiter* Parent;
	
protected:
	
	/** Orbit around parent */
	virtual void Orbit(float DeltaTime);
	
	/** Rotate by ourselves */
	virtual void SelfRotate(float DeltaTime);
	
	/** Total time running */
	float RunningTime;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, Category=Component)
	UArrowComponent* ArrowComp;
	
	UPROPERTY(EditAnywhere, Category=Component)
	float SpeedScale;
};

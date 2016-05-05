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
	
	//////////////////////////////
	// Getters
	
	FORCEINLINE AFournoidCharacter* GetKeeperMaster() const { return MasterCharacter; }
	
	FORCEINLINE float GetKeeperStickDistance() const { return KeeperStickDistance; }
	
	FORCEINLINE float GetKeeperPropelDistance() const { return KeeperPropelDistance; }
	
	FORCEINLINE float GetKeeperMovementSpeed() const { return KeeperMovementSpeed; }
	
	FORCEINLINE float GetKeeperHoverFalloff() const { return KeeperHoverFalloff; }
	
	//////////////////////////////
	// Setters
	
	UFUNCTION(BlueprintCallable, Category = Keeper)
	void SetKeeperMaster(class AFournoidCharacter* Master);
	
	UFUNCTION(BlueprintCallable, Category = Keeper)
	void SetKeeperStickDistance(float NewDistance);
	
	UFUNCTION(BlueprintCallable, Category = Keeper)
	void SetKeeperPropelDistance(float NewDistance);
	
	UFUNCTION(BlueprintCallable, Category = Keeper)
	void SetKeeperMovementSpeed(float NewSpeed);
	
	UFUNCTION(BlueprintCallable, Category = Keeper)
	void SetKeeperHoverFalloff(float NewFalloff);
	
protected:
	virtual void FollowMaster(float DeltaTime);
	
protected:
	UPROPERTY(VisibleAnywhere, Category = Keeper)
	UArrowComponent* ArrowComp;
	
	UPROPERTY(VisibleAnywhere, Category = Keeper)
	USphereComponent* KeeperSphereComp;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	UMovementComponent* KeeperMovement;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	float KeeperStickDistance;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	float KeeperPropelDistance;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	float KeeperMovementSpeed;
	
	UPROPERTY(VisibleAnywhere, Category=Keeper, meta = (AllowPrivateAccess = "true"))
	float KeeperHoverFalloff;
	
private:
	class AFournoidCharacter* MasterCharacter;
	
	FVector MoveDirection;
	
	float RunningTime;
};

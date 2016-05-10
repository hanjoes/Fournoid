// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __FOURNOID_H__
#define __FOURNOID_H__

#include "Engine.h"
#include "FournoidUtils.h"
#include "Net/UnrealNetwork.h"
#include "Characters/FournoidCharacter.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(Fournoid, Log, All);

//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(FournoidInit, Log, All);

//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(FournoidAI, Log, All);

//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(FournoidError, Error, All);

//Logging for Network
DECLARE_LOG_CATEGORY_EXTERN(FournoidNetwork, Warning, All);

/** when you modify this, please note that this information can be saved with instances
 * also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list **/
#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PICKUP		ECC_GameTraceChannel3

#endif

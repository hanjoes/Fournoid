// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Fournoid, "Fournoid" );

//General Log
DEFINE_LOG_CATEGORY(Fournoid);

//Logging during game startup
DEFINE_LOG_CATEGORY(FournoidInit);

//Logging for your AI system
DEFINE_LOG_CATEGORY(FournoidAI);

//Logging for Critical Errors that must always be addressed
DEFINE_LOG_CATEGORY(FournoidError);
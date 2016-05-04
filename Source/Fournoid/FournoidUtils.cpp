// Fill out your copyright notice in the Description page of Project Settings.

#include "Fournoid.h"
#include "FournoidUtils.h"

const static int KEY = INDEX_NONE;
const static float STAY_TIME = 2.0f;


void FournoidUtils::RedMessage(const FString &Msg)
{
    GEngine->AddOnScreenDebugMessage(KEY, STAY_TIME, FColor::Red, Msg);
}

void FournoidUtils::YellowMessage(const FString &Msg)
{
    GEngine->AddOnScreenDebugMessage(KEY, STAY_TIME, FColor::Yellow, Msg);
}

void FournoidUtils::GreenMessage(const FString &Msg)
{
    GEngine->AddOnScreenDebugMessage(KEY, STAY_TIME, FColor::Green, Msg);
}

void FournoidUtils::BlueMessage(const FString &Msg)
{
    GEngine->AddOnScreenDebugMessage(KEY, STAY_TIME, FColor::Blue, Msg);
}


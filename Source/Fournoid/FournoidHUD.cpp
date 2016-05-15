// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"

#define BUTTONTYPE_MAIN_RESTART 	1
#define BUTTONTYPE_MAIN_EXIT 		2

#define BUTTONTYPE_CONFIRM_YES 	1
#define BUTTONTYPE_CONFIRM_NO 	2

#define CANVAS_WHITE if(Canvas) Canvas->SetDrawColor(FColor_White);

//
//Static Consts
//

const FString AFournoidHUD::S_Title_Main = FString("Joy!");
const FString AFournoidHUD::S_Title_Confirm = FString("Exit Game?");

const FString AFournoidHUD::S_Button_Restart = FString("Restart");
const FString AFournoidHUD::S_Button_Exit = FString("Exit");

// Colors 
const FColor AFournoidHUD::FColorBlack = FColor(0, 0, 0, 255);
const FColor AFournoidHUD::FColorRed = FColor(255, 0, 0, 255);
const FColor AFournoidHUD::FColorYellow = FColor(255, 255, 0, 255);
const FColor AFournoidHUD::FColorBlue = FColor(0, 0, 255, 255);
const FColor AFournoidHUD::FColor_White = FColor(255, 255, 255, 255);
// Backgrounds 
const FLinearColor AFournoidHUD::LC_Black = FLinearColor(0, 0, 0, 1);
const FLinearColor AFournoidHUD::LC_Pink = FLinearColor(1, 0, 1, 1);
const FLinearColor AFournoidHUD::LC_Red = FLinearColor(1, 0, 0, 1);
const FLinearColor AFournoidHUD::LC_Yellow = FLinearColor(1, 1, 0, 1);


AFournoidHUD::AFournoidHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshiarTexObj.Object;
}


void AFournoidHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();

	DrawInGameMenu();

	DrawHealthBar();
}

void AFournoidHUD::PostInitializeComponents() {
	Super::PostInitializeComponents();

	//Establish the PC
	ThePC = GetOwningPlayerController();
}

void AFournoidHUD::DrawCrossHair() {
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition((Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5)),
		(Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f)));

	// draw the crosshair
	FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}

void AFournoidHUD::DrawInGameMenu() {
	return;
	//Background
	DrawMaterialSimple(
		MaterialBackground,
		10, 10,
		256,
		512,
		DefaultFontScale
		);

	DrawMainMenuButtons();
}

void AFournoidHUD::DrawHealthBar() {
	auto Character = Cast<AFournoidCharacter>(ThePC->GetPawn());
	if (!Character || Character->IsDead())
	{
		return;
	}

	//Background
	float barX = Canvas->ClipX * HealthBarXOffset;
	float barY = Canvas->ClipY * HealthBarYOffset;

	DrawMaterialSimple(
		HealthBarBackground,
		barX , barY,
		HealthBarWidth,
		HealthBarHeight,
		HealthBarScale
		);
	
	//Health Icon
	FCanvasIcon healthIcon = UCanvas::MakeIcon(HealthIcon, 20, 20);
	float iconX = Canvas->ClipX * HealthIconXOffset;
	float iconY = Canvas->ClipY * HealthIconYOffset;
	Canvas->DrawIcon(healthIcon, iconX, iconY, HealthIconScale);
	
	int Health = Character->GetCharacterHealth();
	FDrawText(
		VerdanaFont, FString::FromInt(Health), iconX + HealthIndicatorOffset, iconY,
		LC_Black, HealthIndicatorScale,
		true, LC_Yellow 
		);

	//Stamina Icon
	FCanvasIcon staminaIcon = UCanvas::MakeIcon(StaminaIcon, 20, 20);
	iconX = Canvas->ClipX * StaminaIconXOffset;
	iconY = Canvas->ClipY * StaminaIconYOffset;
	Canvas->DrawIcon(staminaIcon, iconX, iconY, StaminaIconScale);

	int stamina = Character->GetCharacterStamina();
	FDrawText(
		VerdanaFont, FString::FromInt(stamina), iconX + StaminaIndicatorOffset, iconY,
		LC_Black, StaminaIndicatorScale,
		true, LC_Yellow
		);
}

void AFournoidHUD::DrawAmmoBar() {
	//Background
	DrawMaterialSimple(
		AmmoBarBackground,
		Canvas->ClipX * AmmoBarXOffset, Canvas->ClipY * AmmoBarYOffset,
		AmmoBarWidth,
		AmmoBarHeight,
		AmmoBarScale
		);
}

//Buttons
void AFournoidHUD::DrawMainMenuButtons()
{
	//Start Point
	float xStart = 100;
	float yStart = 110;

	//Background
	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColorBlue); //alpha 120/255

																					  //Text
	FDrawText(
		VerdanaFont, "Restart", xStart + 30, yStart + 20,
		LC_Black, DefaultFontScale,
		true, LC_Red
		);

	//Struct
	//Add Button If Necessary
	//		could be cleared and need refreshing if using a different menu
	//			clear buttons with ButtonsMain.Empty()
	if (ButtonsMain.Num() < 1)
	{
		FButtonStruct newButton = FButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_RESTART;
		newButton.toolTip = "Restart the Game!";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		//Add to correct array
		ButtonsMain.Add(newButton);
	}


	xStart = 100;
	yStart = 410;

	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, FColor(255, 255, 255, 120)); //alpha 120/255

																					  //Text
	FDrawText(
		VerdanaFont, "Exit", xStart + 55, yStart + 20,
		LC_Black, DefaultFontScale,
		true, LC_Red
		);

	if (ButtonsMain.Num() < 2)
	{
		FButtonStruct newButton = FButtonStruct();
		newButton.type = BUTTONTYPE_MAIN_EXIT;
		newButton.toolTip = "Exit the Game!";
		newButton.minX = xStart;
		newButton.maxX = xStart + 150;
		newButton.minY = yStart;
		newButton.maxY = yStart + 80;

		//Add to correct array
		ButtonsMain.Add(newButton);
	}
}
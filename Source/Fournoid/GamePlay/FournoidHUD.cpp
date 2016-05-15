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

	DrawInGameMenuFlag = false;
	ShowCursor = false;
	ConfirmDialogOpen = false;

	TextColor = LC_Black;
	TextOuterColor = LC_Black;
}


void AFournoidHUD::DrawHUD()
{
	if (!ThePC)
	{
		//Attempt to Reacquire PC
		ThePC = GetOwningPlayerController();

		//Could Not Obtain PC
		if (!ThePC) return;
		//~~
	}

	//Multiplayer Safety Check
	if (!ThePC->PlayerInput) return; //not valid for first seconds of a multiplayer client

	PlayerInputCheckes();

	Super::DrawHUD();

	DrawCrossHair();

	DrawInGameMenu();

	DrawHealthBar();

	//================
	//Get New Mouse Position
	//================
	ThePC->GetMousePosition(MouseLocation.X, MouseLocation.Y);

	//Cursor In Buttons
	DrawHUD_CheckCursorInButtons();
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
	if (!DrawInGameMenuFlag) {
		return;
	}

	//Background
	DrawMaterialSimple(
		MaterialBackground,
		Canvas->ClipX * InGameMenuXOffset, Canvas->ClipY * InGameMenuYOffset,
		256,
		512,
		DefaultFontScale
		);

	DrawMainMenuButtons();

	if (ConfirmDialogOpen) {
		DrawConfirm();
	}
}

void AFournoidHUD::DrawConfirm()
{
	//Blue rect with alpha 50%
	FDrawRect(Canvas->SizeX / 2 - 100, Canvas->SizeY / 2 - 50, 200, 100, FLinearColor(0, 0, 1, 0.2333));

	//Confirm Title

	//Draw buttons
	DrawConfirmButtons();
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
	float xStart = Canvas->ClipX * InGameMenuXOffset + ButtonXOffset;
	float yStart = Canvas->ClipY * InGameMenuYOffset + 15;
	FColor buttonColor = FColor(255, 255, 255, 120);

	//Background
	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, buttonColor); //alpha 120/255
	//Text
	FDrawText(
		VerdanaFont, "Restart", xStart + TextXOffset, yStart + TextYOffset,
		TextColor, TextScale,
		true, TextOuterColor
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

	yStart += ButtonYIncrement;

	VDrawTile(ButtonBackground, xStart, yStart, 150, 80, buttonColor); //alpha 120/255
																					  //Text
	FDrawText(
		VerdanaFont, "Exit", xStart + TextXOffset, yStart + TextYOffset,
		TextColor, TextScale,
		true, TextOuterColor
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

void AFournoidHUD::DrawConfirmButtons()
{
	float xStart = Canvas->SizeX / 2 - 100;
	float yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_YES) ColorPtr = &LC_Pink;
	else ColorPtr = &LC_Yellow;

	//Text
	FDrawText(
		VerdanaFont, "Yes", xStart + 30, yStart + 20,
		*ColorPtr, TextScale * 0.8,
		true
		);

	if (ButtonsConfirm.Num() < 1)
	{
		FButtonStruct newButton = FButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_YES;
		newButton.toolTip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//could use GetTextSize to streamline this

		//Add to correct array
		ButtonsConfirm.Add(newButton);
	}

	xStart = Canvas->SizeX / 2 + 20;
	yStart = Canvas->SizeY / 2 - 40;

	//Highlighted?
	if (ActiveButton_Type == BUTTONTYPE_CONFIRM_NO) ColorPtr = &LC_Black;
	else ColorPtr = &LC_Yellow;

	//Text
	FDrawText(
		VerdanaFont, "No", xStart + 30, yStart + 20,
		*ColorPtr, TextScale * 0.8,
		true
		);

	if (ButtonsConfirm.Num() < 2)
	{
		FButtonStruct newButton = FButtonStruct();
		newButton.type = BUTTONTYPE_CONFIRM_NO;
		newButton.toolTip = "";
		newButton.minX = xStart;
		newButton.maxX = xStart + 75;
		newButton.minY = yStart + 20;
		newButton.maxY = yStart + 60;

		//could use GetTextSize to streamline this

		//Add to correct array
		ButtonsConfirm.Add(newButton);
	}
}

void AFournoidHUD::PlayerInputCheckes() {
	if (ThePC->WasInputKeyJustPressed(EKeys::M))
	{
		DrawInGameMenuFlag = !DrawInGameMenuFlag;
		SwitchCursorState();
		SetCursorMoveOnly(!ThePC->IsLookInputIgnored());
		return;
	}
}

void AFournoidHUD::DrawHUD_CheckCursorInButtons()
{
	if (ConfirmDialogOpen)
	{
		CheckCursorInButtonsConfirm();

		//Take Focus Away From All Other buttons
		return;
		//~
	}

	//Main
	CheckCursorInButtonsMain();
}

//Check Buttons
void AFournoidHUD::CheckCursorInButtonsMain()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsMain);

	if (ClickedButtonType == BUTTONTYPE_MAIN_RESTART)
	{
		ThePC->ConsoleCommand("RestartLevel");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_MAIN_EXIT)
	{
		ConfirmDialogOpen = true;
		return;
	}
}

//Check Confirm
void AFournoidHUD::CheckCursorInButtonsConfirm()
{
	//Check Confirm Buttons
	ClickedButtonType = CheckCursorInButton(ButtonsConfirm); //fills global ActiveButton_Type

	if (ClickedButtonType == BUTTONTYPE_CONFIRM_YES)
	{
		ThePC->ConsoleCommand("Exit");
		return;
	}
	if (ClickedButtonType == BUTTONTYPE_CONFIRM_NO)
	{
		ConfirmDialogOpen = false;
		ButtonsConfirm.Empty(); //Buttons not needed anymore
		return;
	}
}

//===============
// Cursor In Buttons
//===============
int32 AFournoidHUD::CheckCursorInButton(const TArray<FButtonStruct>& ButtonArray)
{
	for (int32 b = 0; b < ButtonArray.Num(); b++)
	{
		CurCheckButton = &ButtonArray[b];

		//check cursor in bounds
		if (CurCheckButton->minX <= MouseLocation.X && MouseLocation.X <= CurCheckButton->maxX &&
			CurCheckButton->minY <= MouseLocation.Y && MouseLocation.Y <= CurCheckButton->maxY)
		{

			//Active Button Type
			ActiveButton_Type = CurCheckButton->type;

			//Tool Tip
			ActiveButton_Tip = CurCheckButton->toolTip;

			//Change Cursor
			CursorHoveringInButton = true;

			//Mouse Clicked?
			if (ThePC->WasInputKeyJustPressed(EKeys::LeftMouseButton))
			{
				return ActiveButton_Type;
				//~~
				//no need to check rest of buttons
			}
		}
	}

	//No Click Occurred This Tick
	return -1;
}
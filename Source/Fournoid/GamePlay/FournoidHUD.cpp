// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Fournoid.h"
#include "FournoidHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "Weapons/FournoidWeapon.h"

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
	


	static ConstructorHelpers::FObjectFinder<UTexture2D> HitTextureOb(TEXT("/Game/UserInterface/HitIndicator"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UserInterface/HUDMain"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets02TextureOb(TEXT("/Game/UserInterface/HUDAssets02"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> LowHealthOverlayTextureOb(TEXT("/Game/UserInterface/LowHealthOverlay"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> StaminaTextureOb(TEXT("/Game/UserInterface/Stamina"));

	//Font
	static ConstructorHelpers::FObjectFinder<UFont> BigFontOb(TEXT("/Game/UserInterface/Roboto51"));
	static ConstructorHelpers::FObjectFinder<UFont> NormalFontOb(TEXT("/Game/UserInterface/Roboto18"));
	BigFont = BigFontOb.Object;
	NormalFont = NormalFontOb.Object;

	HitNotifyTexture = HitTextureOb.Object;
	HUDMainTexture = HUDMainTextureOb.Object;
	HUDAssets02Texture = HUDAssets02TextureOb.Object;
	LowHealthOverlayTexture = LowHealthOverlayTextureOb.Object;
	StaminaTexture = StaminaTextureOb.Object;

	HitNotifyIcon[EShooterHudPosition::Left] = UCanvas::MakeIcon(HitNotifyTexture, 158, 831, 585, 392);
	HitNotifyIcon[EShooterHudPosition::FrontLeft] = UCanvas::MakeIcon(HitNotifyTexture, 369, 434, 460, 378);
	HitNotifyIcon[EShooterHudPosition::Front] = UCanvas::MakeIcon(HitNotifyTexture, 848, 284, 361, 395);
	HitNotifyIcon[EShooterHudPosition::FrontRight] = UCanvas::MakeIcon(HitNotifyTexture, 1212, 397, 427, 394);
	HitNotifyIcon[EShooterHudPosition::Right] = UCanvas::MakeIcon(HitNotifyTexture, 1350, 844, 547, 321);
	HitNotifyIcon[EShooterHudPosition::BackRight] = UCanvas::MakeIcon(HitNotifyTexture, 1232, 1241, 458, 341);
	HitNotifyIcon[EShooterHudPosition::Back] = UCanvas::MakeIcon(HitNotifyTexture, 862, 1384, 353, 408);
	HitNotifyIcon[EShooterHudPosition::BackLeft] = UCanvas::MakeIcon(HitNotifyTexture, 454, 1251, 371, 410);

	//KillsBg = UCanvas::MakeIcon(HUDMainTexture, 15, 16, 235, 62);
	//TimePlaceBg = UCanvas::MakeIcon(HUDMainTexture, 262, 16, 255, 62);
	//PrimaryWeapBg = UCanvas::MakeIcon(HUDMainTexture, 543, 17, 441, 81);
	//SecondaryWeapBg = UCanvas::MakeIcon(HUDMainTexture, 676, 111, 293, 50);

	//DeathMessagesBg = UCanvas::MakeIcon(HUDMainTexture, 502, 177, 342, 187);
	HealthBar = UCanvas::MakeIcon(HUDAssets02Texture, 67, 212, 372, 50);
	HealthBarBg = UCanvas::MakeIcon(HUDAssets02Texture, 67, 162, 372, 50);
	HealthIcon = UCanvas::MakeIcon(HUDAssets02Texture, 78, 262, 28, 28);

	StaminaBar = UCanvas::MakeIcon(StaminaTexture, 67, 212, 372, 50);
	StaminaBarBg = UCanvas::MakeIcon(StaminaTexture, 67, 162, 372, 50);
	StaminaIcon = UCanvas::MakeIcon(StaminaTexture, 78, 262, 28, 28);
	//KillsIcon = UCanvas::MakeIcon(HUDMainTexture, 318, 93, 24, 24);
	//TimerIcon = UCanvas::MakeIcon(HUDMainTexture, 381, 93, 24, 24);
	//KilledIcon = UCanvas::MakeIcon(HUDMainTexture, 425, 92, 38, 36);
	//PlaceIcon = UCanvas::MakeIcon(HUDMainTexture, 250, 468, 21, 28);

	Crosshair[EShooterCrosshairDirection::Left] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[EShooterCrosshairDirection::Right] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[EShooterCrosshairDirection::Top] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[EShooterCrosshairDirection::Bottom] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[EShooterCrosshairDirection::Center] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center

	Offsets[EShooterHudPosition::Left] = FVector2D(173, 0);
	Offsets[EShooterHudPosition::FrontLeft] = FVector2D(120, 125);
	Offsets[EShooterHudPosition::Front] = FVector2D(0, 173);
	Offsets[EShooterHudPosition::FrontRight] = FVector2D(-120, 125);
	Offsets[EShooterHudPosition::Right] = FVector2D(-173, 0);
	Offsets[EShooterHudPosition::BackRight] = FVector2D(-120, -125);
	Offsets[EShooterHudPosition::Back] = FVector2D(0, -173);
	Offsets[EShooterHudPosition::BackLeft] = FVector2D(120, -125);


	HitNotifyCrosshair = UCanvas::MakeIcon(HUDMainTexture, 54, 453, 50, 50);

	Offset = 20.0f;
	HUDLight = FColor(175, 202, 213, 255);
	HUDDark = FColor(110, 124, 131, 255);
	ShadowedFont.bEnableShadow = true;

}


void AFournoidHUD::DrawHUD()
{
	ScaleUI = Canvas->ClipY / 1080.0f;


	XScale = Canvas->ClipX;
	YScale = Canvas->ClipY;
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

	DrawAmmoBar();

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
		XScale * MainMenuStartX, YScale * MainMenuStartY,
		XScale * MainMenuWidth,
		YScale * MainMenuHeight,
		1
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

	////Stamina Icon
	//FCanvasIcon staminaIcon = UCanvas::MakeIcon(StaminaIcon, 20, 20);
	//iconX = XScale * StaminaIconStartX;
	//iconY = YScale * StaminaIconStartY;
	//Canvas->DrawIcon(staminaIcon, iconX, iconY, XScale * StaminaIconScale);

	//int stamina = Character->GetCharacterStamina();
	//FDrawText(
	//	VerdanaFont, FString::FromInt(stamina), iconX + XScale * StaminaIndicatorOffset, iconY,
	//	LC_Black, XScale * StaminaIndicatorScale,
	//	true, LC_Yellow
	//	);


	Canvas->SetDrawColor(FColor::White);
	const float HealthPosX = Canvas->OrgX;
	const float HealthPosY = Canvas->ClipY - (Offset + HealthBarBg.VL) * ScaleUI;
	Canvas->DrawIcon(HealthBarBg, HealthPosX, HealthPosY, ScaleUI);
	const float HealthAmount = FMath::Min(1.0f, Character->GetCharacterHealth() / 100);

	FCanvasTileItem TileItem(FVector2D(HealthPosX, HealthPosY), HealthBar.Texture->Resource,
		FVector2D(HealthBar.UL * HealthAmount  * ScaleUI, HealthBar.VL * ScaleUI), FLinearColor::White);
	MakeUV(HealthBar, TileItem.UV0, TileItem.UV1, HealthBar.U, HealthBar.V, HealthBar.UL * HealthAmount, HealthBar.VL);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);

	Canvas->DrawIcon(HealthIcon, HealthPosX + Offset * ScaleUI, HealthPosY + (HealthBar.VL - HealthIcon.VL) / 2.0f * ScaleUI, ScaleUI);


	Canvas->SetDrawColor(FColor::White);
	const float StaminaPosX = HealthBar.UL * ScaleUI;
	const float StaminaPosY = Canvas->ClipY - (Offset + StaminaBarBg.VL) * ScaleUI;
	Canvas->DrawIcon(StaminaBarBg, StaminaPosX, StaminaPosY, ScaleUI);
	const float StaminaAmount = FMath::Min(1.0f, Character->GetCharacterStamina() / 100);

	FCanvasTileItem TileItem2(FVector2D(StaminaPosX, StaminaPosY), StaminaBar.Texture->Resource,
		FVector2D(StaminaBar.UL * StaminaAmount  * ScaleUI, StaminaBar.VL * ScaleUI), FLinearColor::White);
	MakeUV(StaminaBar, TileItem2.UV0, TileItem2.UV1, StaminaBar.U, StaminaBar.V, StaminaBar.UL * StaminaAmount, StaminaBar.VL);
	TileItem2.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem2);

	Canvas->DrawIcon(StaminaIcon, StaminaPosX + Offset * ScaleUI, StaminaPosY + (StaminaBar.VL - StaminaIcon.VL) / 2.0f * ScaleUI, ScaleUI);
}

void AFournoidHUD::DrawAmmoBar() {
	auto Character = Cast<AFournoidCharacter>(ThePC->GetPawn());
	if (!Character || Character->IsDead())
	{
		return;
	}

	//Background
	DrawMaterialSimple(
		AmmoBarBackground,
		XScale * AmmoBarStartX, YScale * AmmoBarStartY,
		XScale * AmmoBarWidth,
		YScale * AmmoBarHeight,
		1
		);

	// Icon
	FCanvasIcon ammoIcon = UCanvas::MakeIcon(AmmoIcon, 20, 20);
	float iconX = XScale * AmmoIconStartX;
	float iconY = YScale * AmmoIconStartY;
	Canvas->DrawIcon(ammoIcon, iconX, iconY, XScale * AmmoIconScale);

	AFournoidWeapon *weapon = Character->GetWeaponActor();
	int32 currentClipSize = weapon->GetCurrentClipSize();
	int32 storeSize = weapon->GetCurrentStoreSize();
	FDrawText(
		VerdanaFont, FString::FromInt(currentClipSize) + "/" + FString::FromInt(storeSize), iconX + XScale * AmmoIndicatorOffset, iconY,
		LC_Black, XScale * AmmoIndicatorScale,
		true, LC_Yellow
		);
}

//Buttons
void AFournoidHUD::DrawMainMenuButtons()
{
	//Start Point
	float xStart = XScale * MainMenuStartX + ButtonXOffset;
	float yStart = YScale * MainMenuStartY + 15;
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
		FMyHUDButtonStruct newButton = FMyHUDButtonStruct();
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
		FMyHUDButtonStruct newButton = FMyHUDButtonStruct();
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
		FMyHUDButtonStruct newButton = FMyHUDButtonStruct();
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
		FMyHUDButtonStruct newButton = FMyHUDButtonStruct();
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
int32 AFournoidHUD::CheckCursorInButton(const TArray<FMyHUDButtonStruct>& ButtonArray)
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

void AFournoidHUD::MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL)
{
	if (Icon.Texture)
	{
		const float Width = Icon.Texture->GetSurfaceWidth();
		const float Height = Icon.Texture->GetSurfaceHeight();
		UV0 = FVector2D(U / Width, V / Height);
		UV1 = UV0 + FVector2D(UL / Width, VL / Height);
	}
}
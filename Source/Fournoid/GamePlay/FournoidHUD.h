// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "Fournoid.h"
#include "GameFramework/HUD.h"
#include "FournoidHUD.generated.h"


namespace EShooterCrosshairDirection
{
	enum Type
	{
		Left = 0,
		Right = 1,
		Top = 2,
		Bottom = 3,
		Center = 4
	};
}

namespace EShooterHudPosition
{
	enum Type
	{
		Left = 0,
		FrontLeft = 1,
		Front = 2,
		FrontRight = 3,
		Right = 4,
		BackRight = 5,
		Back = 6,
		BackLeft = 7,
	};
}

USTRUCT()
struct FMyHUDButtonStruct
{
	GENERATED_USTRUCT_BODY()

	//Vars
	int32		type;
	FString		toolTip;
	float 		minX;
	float 		maxX;
	float 		minY;
	float 		maxY;

	//default properties

	FMyHUDButtonStruct()
	{
		type = -1;
		toolTip = "";
		minX = 0;
		maxX = 0;
		minY = 0;
		maxY = 0;
	}
};

UCLASS()
class AFournoidHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Verdana */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AFournoidHUD)
		UFont* VerdanaFont;

	/** Put Roboto Here */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AFournoidHUD)
		UFont* UE4Font;

	/** Font Scaling Used By Your HUD Code */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AFournoidHUD)
		float DefaultFontScale;

	/* In Game Main Menu Properties*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainMenu)
		float MainMenuStartX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainMenu)
		float MainMenuStartY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainMenu)
		float MainMenuWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MainMenu)
		float MainMenuHeight;

	// T2D 
	/** Cursor */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		UTexture2D* CursorMain;

	/** Hovering */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		UTexture2D* CursorHoveringButton;

	/** Button */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		UTexture2D* ButtonBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		float ButtonXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		float ButtonYIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		float TextXOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		float TextYOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T2D)
		float TextScale;


	/** Stamina icon on the stamina bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		FCanvasIcon StaminaIcon;

	/** Stamina icon additional scale on the stamina bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaIconAdjustScale;

	/** Stamina icon additional x-axis shift on the stamina bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaIconAdjustStartX;

	/** Stamina icon additional y-axis shift on the stamina bar. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
		float StaminaIconAdjustStartY;


	// Materials 
	/** Events */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Materials)
		UMaterialInterface* MaterialBackground;

//Buttons
public:
	TArray<FMyHUDButtonStruct> ButtonsMain;
	TArray<FMyHUDButtonStruct> ButtonsConfirm;

	//Cursor In buttons
	FVector2D MouseLocation;
	void DrawHUD_CheckCursorInButtons();
	void DrawConfirm();
	void DrawConfirmButtons();
	void CheckCursorInButtonsMain();
	void CheckCursorInButtonsConfirm();

	const FMyHUDButtonStruct* CurCheckButton;
	int32 CheckCursorInButton(const TArray<FMyHUDButtonStruct>& ButtonArray);
	int32 ClickedButtonType;
	//States
	bool ConfirmDialogOpen;
	bool InMainMenu;

	int32 		ActiveButton_Type;
	FString 	ActiveButton_Tip;
	bool CursorHoveringInButton;
	
//Colors
public:
	const FLinearColor * ColorPtr;

	//Colors
	static const FColor		FColorBlack;
	static const FColor		FColorRed;
	static const FColor		FColorYellow;
	static const FColor		FColorBlue;
	static const FColor		FColor_White;

	static const FLinearColor LC_Black;
	static const FLinearColor LC_Pink;
	static const FLinearColor LC_Red;
	static const FLinearColor LC_Yellow;

//FString
public:

	//`Titles
	static const FString S_Title_Main;
	static const FString S_Title_Confirm;
	//`Button Text
	static const FString S_Button_Restart;
	static const FString S_Button_Exit;


	AFournoidHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void PostInitializeComponents() override;

	void DrawCrossHair();
	
	void DrawInGameMenu();

	void DrawMainMenuButtons();

	void DrawHealthBar();

	void DrawWeaponHUD();

	void DrawKills();

	void PlayerInputCheckes();

	/** helper for getting uv coords in normalized top,left, bottom, right format */
	void MakeUV(FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL);

	FORCEINLINE void VDrawTile(UTexture2D* tex, float x, float y, float screenX, float screenY, const FColor& TheColor)
	{
		if (!Canvas) return;
		if (!tex) return;
		//~

		Canvas->SetDrawColor(TheColor);

		//Draw
		Canvas->DrawTile(
			tex, x, y, //z pos
			screenX, //screen width
			screenY,  //screen height
			0, //texture start width
			0, //texture start height
			tex->GetSurfaceWidth(), //texture width from start
			tex->GetSurfaceHeight(), //texture height from start
			BLEND_Translucent
			);
	}

	FORCEINLINE void FDrawRect(
		float X, float Y,
		float Width, float Height,
		const FLinearColor& Color
		)
	{
		if (!Canvas) return;
		//

		FCanvasTileItem RectItem(
			FVector2D(X, Y),
			FVector2D(Width, Height),
			Color
			);

		RectItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(RectItem);
	}

	//DrawText
	FORCEINLINE void FDrawText(
		UFont*	TheFont,
		const FString& TheStr,
		const float& X, const float& Y,
		const FLinearColor& TheColor,
		const float& TheScale,
		bool DrawOutline = false,
		const FLinearColor OutlineColor = FLinearColor(0, 0, 0, 1)
		) {
		if (!Canvas) return;
		//

		//Text and Font
		FCanvasTextItem NewText(
			FVector2D(X, Y),
			FText::FromString(TheStr),
			TheFont,
			TheColor
			);

		//Text Scale
		NewText.Scale.Set(TheScale, TheScale);

		//Outline gets its alpha from the main color
		NewText.bOutlined = true;
		NewText.OutlineColor = OutlineColor;
		NewText.OutlineColor.A = TheColor.A * 2;

		//Draw
		Canvas->DrawItem(NewText);
	}

	//Stop Camera From Moving With Mouse
	FORCEINLINE void SetCursorMoveOnly(bool CursorOnly)
	{
		if (!ThePC) return;
		//
		ThePC->SetIgnoreLookInput(CursorOnly);

	}

	//Change Cursor State
	FORCEINLINE void SwitchCursorState() {
		ShowCursor = !ShowCursor;
		ThePC->bShowMouseCursor = ShowCursor;
		ThePC->bEnableClickEvents = ShowCursor;
		ThePC->bEnableMouseOverEvents = ShowCursor;
	}

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	APlayerController *ThePC;
	bool DrawInGameMenuFlag;
	bool ShowCursor;
	FLinearColor TextColor;
	FLinearColor TextOuterColor;
	float XScale;
	float YScale;

	UPROPERTY()
	UFont* BigFont;

	UPROPERTY()
	UFont* NormalFont;

	/** Texture for hit indicator. */
	UPROPERTY()
	UTexture2D* HitNotifyTexture;

	/** texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDMainTexture;

	/** Texture for HUD elements. */
	UPROPERTY()
	UTexture2D* HUDAssets02Texture;

	/** Texture for Stamina bar. */
	UPROPERTY()
	UTexture2D* StaminaTexture;

	/** Overlay shown when health is low. */
	UPROPERTY()
	UTexture2D* LowHealthOverlayTexture;

	/** Icons for hit indicator. */
	UPROPERTY()
	FCanvasIcon HitNotifyIcon[8];

	/** Health bar background icon. */
	UPROPERTY()
	FCanvasIcon HealthBarBg;

	/** Health bar icon. */
	UPROPERTY()
	FCanvasIcon HealthBar;

	/** Health icon on the health bar. */
	UPROPERTY()
	FCanvasIcon HealthIcon;

	/** Stamina bar background icon. */
	UPROPERTY()
	FCanvasIcon StaminaBarBg;

	/** Stamina bar icon. */
	UPROPERTY()
	FCanvasIcon StaminaBar;

	

	/** Crosshair icons (left, top, right, bottom and center). */
	UPROPERTY()
	FCanvasIcon Crosshair[5];

	/** Offsets to display hit indicator parts. */
	FVector2D Offsets[8];

	/** On crosshair indicator that we hit someone. */
	UPROPERTY()
	FCanvasIcon HitNotifyCrosshair;

	/** Primary weapon background icon. */
	UPROPERTY()
	FCanvasIcon PrimaryWeapBg;

	/** Primary weapon icon. */
	UPROPERTY()
	FCanvasIcon PrimaryClipIcon;

	/** Kills icon. */
	UPROPERTY()
	FCanvasIcon KillsIcon;

	/** Kills background. */
	UPROPERTY()
	FCanvasIcon KillsBg;

	/** General offset for HUD elements. */
	float Offset;

	/** Lighter HUD color. */
	FColor HUDLight;

	/** Darker HUD color. */
	FColor HUDDark;

	/** FontRenderInfo enabling casting shadow.s */
	FFontRenderInfo ShadowedFont;

	/** UI scaling factor for other resolutions than Full HD. */
	float ScaleUI;
};


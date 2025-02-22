// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "TopDownShmupCharacter.h"
#include "DwarfCharacter.h"
#include "Lab08HUD.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ALab08HUD : public AHUD
{
	GENERATED_BODY()
	
    //Variable for storing the font
    UPROPERTY()
    UFont * HUDFont;
    
    //Primary draw call for the HUD
    virtual void DrawHUD() override;
    
    ALab08HUD();
    
	
};

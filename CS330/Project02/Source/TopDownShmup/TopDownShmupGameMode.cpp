// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmup.h"
#include "TopDownShmupGameMode.h"
#include "TopDownShmupPlayerController.h"
#include "TopDownShmupCharacter.h"
#include "Lab08HUD.h"
ATopDownShmupGameMode::ATopDownShmupGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownShmupPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
    HUDClass = ALab08HUD::StaticClass();
}
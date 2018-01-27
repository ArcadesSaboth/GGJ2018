// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GGJ18GameMode.h"
#include "GGJ18PlayerController.h"
#include "GGJ18Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ18GameMode::AGGJ18GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGGJ18PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
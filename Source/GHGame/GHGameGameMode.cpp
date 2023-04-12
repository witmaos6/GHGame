// Copyright Epic Games, Inc. All Rights Reserved.

#include "GHGameGameMode.h"
#include "GHGamePlayerController.h"
#include "GHGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGHGameGameMode::AGHGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGHGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
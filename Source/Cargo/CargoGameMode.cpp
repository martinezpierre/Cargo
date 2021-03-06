// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Cargo.h"
#include "CargoGameMode.h"
#include "CargoHUD.h"
#include "CargoCharacter.h"

ACargoGameMode::ACargoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACargoHUD::StaticClass();
}

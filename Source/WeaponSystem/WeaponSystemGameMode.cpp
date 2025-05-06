// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponSystemGameMode.h"
#include "WeaponSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWeaponSystemGameMode::AWeaponSystemGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

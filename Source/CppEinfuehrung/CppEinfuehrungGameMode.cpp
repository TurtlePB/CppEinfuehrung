// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppEinfuehrungGameMode.h"
#include "CppEinfuehrungCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppEinfuehrungGameMode::ACppEinfuehrungGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

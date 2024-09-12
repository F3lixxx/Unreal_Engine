// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDS_ProGameMode.h"
#include "TDS_ProCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDS_ProGameMode::ATDS_ProGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

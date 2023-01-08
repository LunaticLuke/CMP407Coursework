// Copyright Epic Games, Inc. All Rights Reserved.

#include "CMP407LukeMcFarlaneGameMode.h"

#include "AkAmbientSound.h"
#include "AkGameplayStatics.h"
#include "CMP407LukeMcFarlaneCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACMP407LukeMcFarlaneGameMode::ACMP407LukeMcFarlaneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}

void ACMP407LukeMcFarlaneGameMode::BeginPlay()
{
	Super::BeginPlay();
	

}

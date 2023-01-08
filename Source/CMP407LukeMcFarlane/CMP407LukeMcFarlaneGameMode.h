// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AkAudioEvent.h"
#include "AudioManager.h"
#include "GameFramework/GameModeBase.h"
#include "CMP407LukeMcFarlaneGameMode.generated.h"

UCLASS(minimalapi)
class ACMP407LukeMcFarlaneGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACMP407LukeMcFarlaneGameMode();
	
	virtual void BeginPlay() override;


protected:

};



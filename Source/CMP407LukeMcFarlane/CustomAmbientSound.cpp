// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAmbientSound.h"

#include "AkAudioDevice.h"
#include "AkComponent.h"

// Sets default values
ACustomAmbientSound::ACustomAmbientSound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the AK component and make it the root component
	WwiseAudioComponent = CreateDefaultSubobject<UAkComponent>("Audio Component");
	SetRootComponent(WwiseAudioComponent);
}

UAkComponent* ACustomAmbientSound::GetAKComponent()
{
	return WwiseAudioComponent;
}

// Called when the game starts or when spawned
void ACustomAmbientSound::BeginPlay()
{
	Super::BeginPlay();
	//If a switch has been specified
	if(SwitchToSet)
	{
		//Set the switch of the same name as the specified group name equal to this value
		WwiseAudioComponent->SetSwitch(SwitchToSet,SwitchGroupName,"");
	}
	//Start the relevant Wwise event.
	WwiseAudioComponent->PostAkEventByName(EventName);
}




// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUI.h"

#include "AkAudioDevice.h"
#include "AkComponent.h"
#include "AudioManager.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

void UPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
	//Bind each slider to their respective value functions. Whenever their values are changed, these functions will be triggered.
	MusicVolumeSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetMusicVolume);
	SFXVolumeSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetSFXVolume);
	RPMSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetRPM);
	EngineLoadSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetEngineLoad);
	MasterSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetMasterVolume);
	AmbienceSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetAmbienceVolume);
	VehicleSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetVehicleVolume);
	FootstepSlider->OnValueChanged.AddDynamic(this,&UPlayerUI::SetFootstepVolume);
	
	//Set the Music and SFX volumes to match the sliders
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Music_Volume"), MusicVolumeSlider->Value, 0, NULL);
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_SFX_Volume"), SFXVolumeSlider->Value, 0, NULL);
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Master_Volume"), MasterSlider->Value, 0, NULL);
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Footsteps_Volume"), FootstepSlider->Value, 0, NULL);
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Vehicle_Volume"), VehicleSlider->Value, 0, NULL);
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Ambience_Volume"), AmbienceSlider->Value, 0, NULL);

	//Create an actor array to use as output for the GetAllActorsOfClass function.
	TArray<AActor*> Actors;
	//Get the AudioManager, output to the actors array.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AAudioManager::StaticClass(),Actors);
	//There's only ever one audio manager so the one that is needed is the first element of the array. Cast the actor to the audiomanager format.
	MechanicAudioComponent = Cast<AAudioManager>(Actors[0])->GetMechanicAkComponent();

	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_RPM"), RPMSlider->Value, 0, MechanicAudioComponent->GetOwner());
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Engine_Load"), EngineLoadSlider->Value, 0, MechanicAudioComponent->GetOwner());
	
	//Set the text of each slider to match the slider's value.
	MusicText->SetText(FText::AsNumber(MusicVolumeSlider->Value));
	SFXText->SetText(FText::AsNumber(SFXVolumeSlider->Value));
	RPMText->SetText(FText::AsNumber(RPMSlider->Value));
	EngineLoadText->SetText(FText::AsNumber(EngineLoadSlider->Value));
	VehicleText->SetText(FText::AsNumber(VehicleSlider->Value));
	FootstepText->SetText(FText::AsNumber(FootstepSlider->Value));
	MasterText->SetText(FText::AsNumber(MasterSlider->Value));
	AmbienceText->SetText(FText::AsNumber(AmbienceSlider->Value));
}

void UPlayerUI::SetMusicVolume(float Value)
{
	//Set the RTPC music value equal to the slider's. Don't specify an actor as music volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Music_Volume"), Value, 0, NULL);
	//Update the text to reflect this.
	MusicText->SetText(FText::AsNumber(Value));
}

void UPlayerUI::SetSFXVolume(float Value)
{
	//Set the RTPC SFX volume value equal to the slider's. Don't specify an actor as SFX volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_SFX_Volume"), Value, 0, NULL);
	//Update the text to reflect this.
	SFXText->SetText(FText::AsNumber(Value));
}

void UPlayerUI::SetRPM(float value)
{
	//Set the RTPC RPM value of the mechanics car equal to the slider's. Specify the mechanics car as an actor as each vehicle instance has their own RTPC values. 
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_RPM"), value, 0, MechanicAudioComponent->GetOwner());
	//Update the text to reflect this.
	RPMText->SetText(FText::AsNumber(value));
}

void UPlayerUI::SetEngineLoad(float value)
{
	//Set the RTPC Engine Load value of the mechanics car equal to the slider's. Specify the mechanics car as an actor as each vehicle instance has their own RTPC values. 
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Engine_Load"), value, 0, MechanicAudioComponent->GetOwner());
	//Update the text to reflect this.
	EngineLoadText->SetText(FText::AsNumber(value));
}

void UPlayerUI::SetAmbienceVolume(float value)
{
	//Set the RTPC ambience volume value equal to the slider's. Don't specify an actor as SFX volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Ambience_Volume"), value, 0, NULL);
	//Update the text to reflect this.
	AmbienceText->SetText(FText::AsNumber(value));
}

void UPlayerUI::SetVehicleVolume(float value)
{
	//Set the RTPC vehicle volume value equal to the slider's. Don't specify an actor as SFX volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Vehicle_Volume"), value, 0, NULL);
	//Update the text to reflect this.
	VehicleText->SetText(FText::AsNumber(value));
}

void UPlayerUI::SetFootstepVolume(float value)
{
	//Set the RTPC footstep volume value equal to the slider's. Don't specify an actor as SFX volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Footsteps_Volume"), value, 0, NULL);
	//Update the text to reflect this.
	FootstepText->SetText(FText::AsNumber(value));
}

void UPlayerUI::SetMasterVolume(float value)
{
	//Set the RTPC footstep volume value equal to the slider's. Don't specify an actor as SFX volume is a global value
	FAkAudioDevice::Get()->SetRTPCValue(*FString("RTPC_Master_Volume"), value, 0, NULL);
	//Update the text to reflect this.
	MasterText->SetText(FText::AsNumber(value));
}

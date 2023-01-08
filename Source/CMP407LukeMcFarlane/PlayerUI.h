// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PlayerUI.generated.h"


class USlider;
/**
 * @brief This class handles the user interface and its interactions with Wwise's RTPC system.
 */
UCLASS()
class CMP407LUKEMCFARLANE_API UPlayerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


protected:

	//Bind all of the sliders
	UPROPERTY(meta=(BindWidget))
	USlider* MusicVolumeSlider;
	UPROPERTY(meta=(BindWidget))
	USlider* SFXVolumeSlider;
	UPROPERTY(meta=(BindWidget))
	USlider* RPMSlider;
	UPROPERTY(meta=(BindWidget))
	USlider* EngineLoadSlider;
	UPROPERTY(meta=(BindWidget))
    USlider* AmbienceSlider;
    UPROPERTY(meta=(BindWidget))
	USlider* VehicleSlider;
	UPROPERTY(meta=(BindWidget))
	USlider* FootstepSlider;
	UPROPERTY(meta=(BindWidget))
	USlider* MasterSlider;
	
	//Bind all of the text blocks.
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MusicText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* SFXText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* RPMText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* EngineLoadText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* AmbienceText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* VehicleText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* FootstepText;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MasterText;

	/**
	 * @brief Sets the WWise music volume RTPC equal to the slider's
	 * @param Value The slider's value to set.
	 */
	UFUNCTION()
	void SetMusicVolume(float Value);
	/**
	 * @brief Sets the WWise SFX volume RTPC equal to the slider's
	 * @param Value The slider's value to set
	 */
	UFUNCTION()
	void SetSFXVolume(float Value);
	/**
	 * @brief Sets the Wwise RPM RTPC value of the mechanic's car equal to the slider's
	 * @param value The slider's value to set.
	 */
	UFUNCTION()
	void SetRPM(float value);
	/**
	 * @brief Sets the Wwise Engine Load RTPC value of the mechanic's car equal to the slider's
	 * @param value The slider's value to set.
	 */
	UFUNCTION()
	void SetEngineLoad(float value);
	UFUNCTION()
	void SetAmbienceVolume(float value);
	UFUNCTION()
	void SetVehicleVolume(float value);
	UFUNCTION()
	void SetFootstepVolume(float value);
	UFUNCTION()
	void SetMasterVolume(float value);

	//The AK component attached to the mechanic's car.
	class UAkComponent* MechanicAudioComponent;
};

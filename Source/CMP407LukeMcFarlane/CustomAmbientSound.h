// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomAmbientSound.generated.h"


//This class triggers a Wwise event but also features functionality to set a switch on it also. This was I was easily able to add ambience to the scene using one script whilst just switching out the switch group names and event names.
UCLASS()
class CMP407LUKEMCFARLANE_API ACustomAmbientSound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomAmbientSound();
	/**
	 * @brief Get the AK component attacehd to this sound.
	 * @return The Ak component present on this actor.
	 */
	class UAkComponent* GetAKComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief An ak audio component to play the sound from. 
	 */
	UPROPERTY(EditAnywhere)
	class UAkComponent* WwiseAudioComponent;

	/**
	 * @brief The switch value to set
	 */
	UPROPERTY(EditAnywhere)
	class UAkSwitchValue* SwitchToSet;
	/**
	 * @brief The name of the switch group to set the switch on
	 */
	UPROPERTY(EditAnywhere)
	FString SwitchGroupName;
	/**
	 * @brief The name of the WWise event to trigger
	 */
	UPROPERTY(EditAnywhere)
	FString EventName;
	

};

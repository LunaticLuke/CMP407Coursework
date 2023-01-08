// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AkAmbientSound.h"
#include "AkAudioEvent.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

class UBoxComponent;

UCLASS()
class CMP407LUKEMCFARLANE_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioManager();

	UAkComponent* GetMechanicAkComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TArray<AAkAmbientSound*> CashRegisters;
	/**
	 * @brief An array of all Wwise events. Referencing them here ensures they are packaged within the build.
	 */
	UPROPERTY(EditAnywhere)
	TArray<class UAkAudioEvent*> Events;
	/**
	 * @brief An array of all Wwise switches. Referencing them here ensures they are packaged within the build.
	 */
	UPROPERTY(EditAnywhere)
	TArray<class UAkSwitchValue*> Switches;
	/**
	 * @brief An array of all Wwise triggers. Referencing them here ensures they are packaged within the build.
	 */
	UPROPERTY(EditAnywhere)
	TArray<class UAkTrigger*> Triggers;
	UPROPERTY(EditAnywhere)
	TArray<class UAkStateValue*> States;

	
	void CashRegisterSounds();
	//Stores a reference to the car sound that can be manipulated via UI as part of RTPC demo.
	UPROPERTY(EditAnywhere)
	class ACustomAmbientSound* MechanicCar;
	//A timer handle to allow timer based functions.
	FTimerHandle Ticker;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	
};

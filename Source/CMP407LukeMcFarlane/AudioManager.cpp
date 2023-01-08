// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "CustomAmbientSound.h"
#include "../Plugins/Wwise/Source/AkAudio/Classes/AkGameplayStatics.h"
#include "Components/BoxComponent.h"


// Sets default values
AAudioManager::AAudioManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

UAkComponent* AAudioManager::GetMechanicAkComponent()
{
	return MechanicCar->GetAKComponent();
}

// Called when the game starts or when spawned
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AAudioManager::CashRegisterSounds,1.0f,true,0);
}

void AAudioManager::CashRegisterSounds()
{
	for(int i = 0; i < CashRegisters.Num(); i++)
	{
		int RandNum = FMath::RandRange(0,100);
		
		if( RandNum <= 40)
		{
			CashRegisters[i]->StopAmbientSound();
			CashRegisters[i]->StartAmbientSound();
		}
	}
}

// Called every frame
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}












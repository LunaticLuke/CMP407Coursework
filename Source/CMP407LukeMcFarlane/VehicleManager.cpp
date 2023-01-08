// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleManager.h"

#include "Vehicle.h"
#include "Components/ArrowComponent.h"

// Sets default values
AVehicleManager::AVehicleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Configure the spawn point as a root component.
	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("Spawn Point");
	SetRootComponent(SpawnPoint);
}

// Called when the game starts or when spawned
void AVehicleManager::BeginPlay()
{
	Super::BeginPlay();
	//Set a timer that calls the spawn vehicle method after a set amount of settings on loop. 
	GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AVehicleManager::SpawnVehicle,SpawnTimer,true,InitialDelay);
}

void AVehicleManager::SpawnVehicle()
{
	//Random number between 0 and 100
	int RandChance = FMath::RandRange(0,100);
	//If the chance is within the chance of spawning.
	if(RandChance <= ChanceOfSpawn)
	{
		//Find another random number between 0 and 100 to determine whether it should be a police car or not
		int RandNumber = FMath::RandRange(0,100);

		//Sapwn the vehicle.
		AVehicle* SpawnedVehicle = GetWorld()->SpawnActor<AVehicle>(GetActorLocation(),GetActorRotation());
		
		//15% chance of police car
		if(RandNumber <= 15)
		{
			//Random index 
			int RandomVehicleNum = FMath::RandRange(0,PotentialPoliceVehicles.Num() - 1);
			//Set the spawned vehicle equal to the random police car, set it along the specified path length and confirm that it is a police car.
			SpawnedVehicle->SetVehicleMesh(PotentialPoliceVehicles[RandomVehicleNum],VehiclePathLength,true);
			//Pass rtpc through
			SpawnedVehicle->SetRtpc(RTPCToSet);
		}
		else //85% chance of normal car
		{
			//Random index
			int RandomVehicleNum = FMath::RandRange(0,PotentialVehicles.Num() - 1);
			
			SpawnedVehicle->SetVehicleMesh(PotentialVehicles[RandomVehicleNum],VehiclePathLength,false);
			SpawnedVehicle->SetRtpc(RTPCToSet);
		}
		//Disable collision as this vehicle isnt configured for physics and is fast moving
		//The main focus is on the audio produced so collision isnt necessary
		SpawnedVehicle->SetActorEnableCollision(false);
	}
}




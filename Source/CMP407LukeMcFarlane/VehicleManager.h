// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleManager.generated.h"


class UArrowComponent;
class UAkRtpc;

UCLASS()
class CMP407LUKEMCFARLANE_API AVehicleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief An array of vehicle meshes that could be used for the spawned vehicles
	 */
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> PotentialVehicles;

	/**
	 * @brief An array of police vehicle meshes that could be used for spawned police vehicles. 
	 */
	UPROPERTY(EditAnywhere)
	TArray<USkeletalMesh*> PotentialPoliceVehicles;

	// A timer to handle the spawn timers.
	FTimerHandle Ticker;

	//The root component at which the vehicles will be spawned.
	UArrowComponent* SpawnPoint;

	//The RTPC to pass through to the vehicles.
	UPROPERTY(EditAnywhere)
	UAkRtpc* RTPCToSet;

	/**
	 * @brief Spawns a vehicle at the root component
	 */
	void SpawnVehicle();

	//How long should the vehicle drive for before despawning.
	UPROPERTY(EditAnywhere)
	float VehiclePathLength = 10000;
	//Upon running the scene, how long should pass before first spawn
	UPROPERTY(EditAnywhere)
	float InitialDelay = 3.0f;
	//How often should the spawn method run in seconds.
	UPROPERTY(EditAnywhere)
	float SpawnTimer;
	//Each time the spawn method runs, the chance of a vehicle actually being spawmed.
	UPROPERTY(EditAnywhere)
	float ChanceOfSpawn = 100;



};

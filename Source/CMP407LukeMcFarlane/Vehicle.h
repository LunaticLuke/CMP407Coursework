// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AkComponent.h"
#include "CMP407LukeMcFarlaneCharacter.h"
#include "GameFramework/Actor.h"
#include "Vehicle.generated.h"


class USkeletalMesh;
class USkeletalMeshComponent;
class USceneComponent;
class UAkRtpc;


//This class handles behaviour on the vehicles including calculating the doppler effect.
UCLASS()
class CMP407LUKEMCFARLANE_API AVehicle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//The vehicle's mesh.
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* VehicleMesh;
	
	//Scene component used as the root of this actor as well as the pivot.
	USceneComponent* RootPivot;

	//The destination to which the vehicle should travel.
	FVector TargetPoint;
	
	//Where the vehicle should be spawned and start its journey.
	FVector StartingPoint;
	
	//States whether the vehicle is currently driving or not
	bool bDriving = false;
	
	//States whether an actor is in front of the car or not.
	bool bActorInFront = false;

	//Is the braking timer currently active.
	bool bTimerActive = false;
	
	/**
	 * @brief Fires a Ray In Front Of The vehicle. if something blocks the car, the car stops
	 */
	void CheckForBlockingPeople();

	//How far along the path between the starting and ending point is the vehicle currently.
	//Scale of 0-1 
	float PathProgress = 0;
	
	//The WWise component to play the sound from.  
	UPROPERTY(EditAnywhere)
	UAkComponent* AkComponent;

	/**
	 * @brief Calculates the doppler effect for this vehicle using relative velocities of player and vehicle.
	 * @return A value between -1 - 1 to configure the doppler RTPC
	 */
	double DopplerEffectCalculation();

	// A reference to the player
	APawn* Player;

	//The Doppler RTPC
	UAkRtpc* RTPC;

	//Stores where the vehicle was last frame.
	FVector OldPosition;

	//Timer handle used for braking timers.
	FTimerHandle Ticker;
	/**
	 * @brief This function causes the vehicle to move again after having braked
	 */
	UFUNCTION()
	void ResumeDriving();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Initializes the vehicle mesh and relevant parameters
	 * @param MeshToSet The Vehicle's mesh
	 * @param DistanceToTravel //How far the car should travel
	 * @param bIsPoliceCar //Whether the current vehicle is a police vehicle or not
	 */
	void SetVehicleMesh(USkeletalMesh* MeshToSet, float DistanceToTravel, bool bIsPoliceCar);

	/**
	 * @brief Sets the RTPC 
	 * @param RTPCToSet The RTPC to use for doppler calculations.
	 */
	void SetRtpc(UAkRtpc* RTPCToSet);
	

};

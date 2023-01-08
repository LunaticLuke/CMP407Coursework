// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FanComponent.generated.h"


//This class handles the rotation of an actor to simulate the movement of a fan. This was an effective demonstration of cone attenuation.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CMP407LUKEMCFARLANE_API UFanComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFanComponent();

protected:

	// The minimum value the fan should rotate to 
    UPROPERTY(EditAnywhere)
    float MinRotation;
	
    //The maximum value the fan should rotate to.
     UPROPERTY(EditAnywhere)
      float MaxRotation;
	
	// How quickly the fan should rotate per second. 
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 5;
	
	//States whether the fan is rotating towards the min value or not right now. Is it going left or right.
	bool bRotatingTowardsMin = true;
	
	//States whether the fan is able to rotate at the moment. 
	bool bCanRotate = true;
	/**
	 * @brief Reset the can rotate boolean. 
	 */
	UFUNCTION()
	void ResetCanRotateFlag();

	//A timer to hold carry out the delayed movement of fan.
	FTimerHandle Ticker;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

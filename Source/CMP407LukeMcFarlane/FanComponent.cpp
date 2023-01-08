// Fill out your copyright notice in the Description page of Project Settings.


#include "FanComponent.h"

// Sets default values for this component's properties
UFanComponent::UFanComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UFanComponent::ResetCanRotateFlag()
{
	bCanRotate = true;
}

// Called every frame
void UFanComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//If the fan is able to rotate and is rotating towards the minimum value
	if(bRotatingTowardsMin && bCanRotate)
	{
		//Rotate the yaw to the left by the speed. Multiply be deltaTime to carry this movement out over time.
		GetOwner()->AddActorWorldRotation(FRotator(0,-RotationSpeed * DeltaTime,0));
		
		//If the fan's Yaw is within a 2.0 range to the minimum rotation
		if(FMath::IsNearlyEqual(GetOwner()->GetActorRotation().Yaw,MinRotation,2.0f))
		{
			//No longer rotating towards the minimum value
			bRotatingTowardsMin = false;
			//Cannot rotate right now
			bCanRotate = false;
			//Start a timer that, after 5 seconds, will resume fan rotation. This creates realistic fan movement where it will remain still for a short time before going the other way.
			GetWorld()->GetTimerManager().SetTimer(Ticker,this,&UFanComponent::ResetCanRotateFlag,5.0f,false,5.0f);
		}
	}
	//If rotating towards the max
	else
	{
		//And can rotate right now
		if(bCanRotate)
		{
			//Rotate the yaw to the right by the rotation speed over time
			GetOwner()->AddActorWorldRotation(FRotator(0,RotationSpeed * DeltaTime,0));
			//Check for the 2 range 
			if(FMath::IsNearlyEqual(GetOwner()->GetActorRotation().Yaw,MaxRotation,2.0f))
			{
				//Now rotating towards the min again
				bRotatingTowardsMin = true;
				//Cannot rotate rightnow
				bCanRotate = false;
				//Start a timer that, after 5 seconds, will resume fan rotation. This creates realistic fan movement where it will remain still for a short time before going the other way.
				GetWorld()->GetTimerManager().SetTimer(Ticker,this,&UFanComponent::ResetCanRotateFlag,5.0f,false,5.0f);
			}
		}
	}
}


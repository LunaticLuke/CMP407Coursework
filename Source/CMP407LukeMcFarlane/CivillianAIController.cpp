// Fill out your copyright notice in the Description page of Project Settings.


#include "CivillianAIController.h"

#include "AkAudioDevice.h"
#include "Kismet/GameplayStatics.h"

void ACivillianAIController::BeginPlay()
{
	Super::BeginPlay();

	
	//Fill up waypoints array with all waypoints from within world.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATargetPoint::StaticClass(),Waypoints);
	
	//Find a random waypoint to go to.
	GoToRandomWaypoint();
	
	//Get a reference to the player's actor 
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	
	//If capable of chasing, start a looping timer that checks if the player is within range every 0.5 seconds. This is more efficient than running it every frame
	GetWorld()->GetTimerManager().SetTimer(ChaseTicker,this, &ACivillianAIController::DeterminePlayerDistance,0.5f,true);


}

ATargetPoint* ACivillianAIController::GetRandomWaypoint()
{
	//Get a random index 
	int index = FMath::RandRange(0,Waypoints.Num() - 1);
	//Return the waypoint of that randomised index,
	return Cast<ATargetPoint>(Waypoints[index]);
}

void ACivillianAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//When the move is completed, start a timer that will find a new waypoint to travel to after a random period of time between 1 and 6 seconds. This makes the NPC wait at a point they've went to for a few seconds as opposed to walking infinitely.
	GetWorld()->GetTimerManager().SetTimer(Ticker,this, &ACivillianAIController::GoToRandomWaypoint,FMath::RandRange(1.0f,6.0f),false);
}

void ACivillianAIController::GoToRandomWaypoint()
{
	//If not currently chasing the player.
	if(!bChasing)
	{
		//Move to a random waypoint.
		MoveToActor(GetRandomWaypoint());
	}
}

void ACivillianAIController::DeterminePlayerDistance()
{
	//If the player actor reference has been successfully set and this NPC instance is capable of chasing.
	if(PlayerActor && bChaser)
	{
		//If the distance between the player and this NPC within the range of 1.5 meters. 
		if(FVector::Distance(GetPawn()->GetActorLocation(),PlayerActor->GetActorLocation()) <= 1500.0f)
		{
			//If not currently chasing
			if(!bChasing)
			{
				//start chasing
				bChasing = true;
				//Move to the player
				MoveToActor(PlayerActor);
				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Cyan, "Within Range");
				//Trigger the WWise event that triggers the stinger.
				FAkAudioDevice::Get()->PostEvent("ToTense",PlayerActor);
				//Switch the WWise music state once at the start of a chase.
				FAkAudioDevice::Get()->SetState(TEXT("Music"),TEXT("Tense"));
			}
		}
		//If the player is further away than 1.5 meters
		else
		{
			//If currently chasing.
			if(bChasing)
			{
				//End the chasse.
				bChasing = false;
				//Resume going back to a random waypoint. 
				GoToRandomWaypoint();
				//Trigger the end chase stinger through a wwise event
				FAkAudioDevice::Get()->PostEvent("ToAmbient",PlayerActor);
				//Switch the wwise music state once at the end of a chase. 
				FAkAudioDevice::Get()->SetState(TEXT("Music"),TEXT("Ambient"));
			}
		}

	
	}
}

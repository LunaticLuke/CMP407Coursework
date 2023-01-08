// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "CivillianAIController.generated.h"

/**
 * @brief This class controls the behaviour of every NPC on the map. 
 */
UCLASS()
class CMP407LUKEMCFARLANE_API ACivillianAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;
	
	/**
	 * @brief States whether this NPC instance has the ability to chase the player.
	 */
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bChaser = false;
private:
	/**
	 * @brief An array containing all possible destinations for the AI agent.
	 */
	UPROPERTY(EditAnywhere, Category="Test")
	TArray<AActor*> Waypoints;
	/**
	 * @brief Finds a random point from all possible destinations.
	 * @return A random destination point from the waypoint array
	 */
	UFUNCTION()
	ATargetPoint* GetRandomWaypoint();
	/**
	 * @brief Handles the AI's behaviour when they reach their destination
	 */
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	/**
	 * @brief A timer to handle how long the NPC waits at their destination once they reach it.
	 */
	FTimerHandle Ticker;
	/**
	 * @brief A timer to handle times between player distance checks for chase behaviour
	 */
	FTimerHandle ChaseTicker;

	/**
	 * @brief States whether the NPC is actively chasing the player.
	 */
	bool bChasing = false;
	/**
	 * @brief A reference to the player's actor object.
	 */
	AActor* PlayerActor;

	/**
	 * @brief Sets the NPCs destination to a random waypoint provided they aren't chasing the player.
	 */
	UFUNCTION()
	void GoToRandomWaypoint();

	/**
	 * @brief Finds the distance between the player and this NPC. If within range, starts a chase. Ends the chase if player is out of range.
	 */
	void DeterminePlayerDistance();
	
	
};

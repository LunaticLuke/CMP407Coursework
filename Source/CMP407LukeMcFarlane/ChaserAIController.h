// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChaserAIController.generated.h"

/**
 * 
 */
UCLASS()
class CMP407LUKEMCFARLANE_API AChaserAIController : public AAIController
{
	GENERATED_BODY()

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	AActor* PlayerActor;

	FVector StartingPosition;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaserAIController.h"

#include "Kismet/GameplayStatics.h"

void AChaserAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
}

void AChaserAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

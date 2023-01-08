// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopEntrance.generated.h"


class UBoxComponent;

//This class simply handles a trigger box that triggers an event when a character passes through.
UCLASS()
class CMP407LUKEMCFARLANE_API AShopEntrance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShopEntrance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * @brief The trigger box to check for overlaps in.
	 */
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;

public:	

// Function called whenever an overlap occurs with the trigger box.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
};

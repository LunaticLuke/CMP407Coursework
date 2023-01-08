// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopEntrance.h"

#include "AkAudioDevice.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"


// Sets default values
AShopEntrance::AShopEntrance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the trigger box and make it the root component.
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Box"));
	SetRootComponent(CollisionBox);
}

// Called when the game starts or when spawned
void AShopEntrance::BeginPlay()
{
	Super::BeginPlay();
	//Bind the overlap event to the trigger box. It will be called whenever an overlap is detected. 
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&AShopEntrance::OnOverlapBegin);
}


void AShopEntrance::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//If the overlapped actor is a character
	if(Cast<ACharacter>(OtherActor))
	{
		
	//Trigger the entering shop WWise event on this actor.
		FAkAudioDevice::Get()->PostEvent("EnterShop",this);
	}
}


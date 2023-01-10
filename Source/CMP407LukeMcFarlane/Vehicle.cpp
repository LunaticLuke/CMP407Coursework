// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

#include "AkAudioDevice.h"
#include "CMP407LukeMcFarlaneCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Set up root component
	RootPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Pivot"));
	SetRootComponent(RootPivot);

	//Create the vehicle mesh
	VehicleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Vehicle Mesh"));
	VehicleMesh->SetupAttachment(RootPivot);

	//Set up the WWise AK component.
	AkComponent = CreateDefaultSubobject<UAkComponent>(TEXT("Ak Component"));
	AkComponent->SetupAttachment(RootPivot);
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();

	//VehicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//VehicleMesh->SetCollisionObjectType((ECollisionChannel::ECC_PhysicsBody));

	//Get a reference to the player
	Player = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	//Fill in the old postion with the current position so that there aren't inaccurate calculations based on 0,0,0
	OldPosition = GetActorLocation();
	VehicleMesh->SetSimulatePhysics(false);
}


void AVehicle::CheckForBlockingPeople()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	
	FVector TraceStart = (GetActorLocation() + (GetActorUpVector() * 50));
	//Fire a 8 meters (800cm) ray ahead of the car
	FVector TraceEnd = TraceStart + GetActorForwardVector() * 800.0f;

	
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Pawn, QueryParams);
	
	//If there's a blocking hit
	if(Hit.bBlockingHit)
	{
		//Stop drivin
		bDriving = false;
		//FAkAudioDevice::Get()->SetSwitch(TEXT("DrivingBraking"),TEXT("Braking"),this);
		//Play the braking sound
		AkComponent->SetSwitch(nullptr,TEXT("DrivingBraking"),TEXT("Braking"));
		//There's an actor in front
		bActorInFront = true;
	}
	else //No hit
	{
		//No actor in front
		bActorInFront = false;
		//If not driving and a timer isnt already active
		if(!bDriving && !bTimerActive)
		{
			//Start a timer that, after 4 seconds will start to drive again (Unless a character steps in the way again)
			GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AVehicle::ResumeDriving,4.0f,false,4.0f);
			//Timer is now active
			bTimerActive = true;
		}
		
	}
}

double AVehicle::DopplerEffectCalculation()
{
	//Get the players velocity as a single number
	auto PlayerVeloctiy = Player->GetVelocity().Length();

	//Find out how far the vehicle has travelled between this frame and last 
	auto Distance =GetActorLocation() - OldPosition;
	//Calculate the velocity using speed= distance/time;
	// Velocity = Movement between frames/ time.deltatime (the time the frame took to run)
	auto VehicleVelocity = Distance.Length()/GetWorld()->GetDeltaSeconds();
	//Update the old postion to reflect this frame's position.
	OldPosition = GetActorLocation();
	
	//For the sake of the moving vehicles, the engine load and rpm are just set to a constant value (as these vehicles dont use proper physics)
	//The mechanics car example within the Player Ui script shows this system being used in a dynamic fashion.
	AkComponent->SetRTPCValue(nullptr,1,0,TEXT("RTPC_Engine_Load"));
	AkComponent->SetRTPCValue(nullptr,3000,0,TEXT("RTPC_RPM"));
	
	//Dot product to determine whether the vehicle is coming towards player or moving away.
	auto PlayerDotProduct = GetDotProductTo(Player);

	//Find the relative velocity 
	auto RelativeVelocity = PlayerVeloctiy - VehicleVelocity;
	
	//Find acceleration/rate of velocity
	auto RateOfVelocity = RelativeVelocity * PlayerDotProduct;

	//Clamp between - 1 and 1
	auto ClampedValue = RateOfVelocity/VehicleVelocity;

	//GEngine->AddOnScreenDebugMessage(-1, 0.01f, FColor::Cyan, FString::SanitizeFloat(ClampedValue));
	
	return ClampedValue;
	
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If driving
	if(bDriving)
	{
		//Set the doppler rtpc value equal to the calculation
		AkComponent->SetRTPCValue(RTPC,DopplerEffectCalculation(),0,TEXT("RTPC_Doppler"));
	}
	//If braked
	else
	{
		//No engine load and no revolutions per minute, idle engine
		AkComponent->SetRTPCValue(nullptr,0,0,TEXT("RTPC_Engine_Load"));
		AkComponent->SetRTPCValue(nullptr,0,0,TEXT("RTPC_RPM"));
	}

	//if driving and havent reached end of path
	if(bDriving && PathProgress < 1)
	{
		//Linearly interpolate towards end location
		FVector CurrentPosition = FMath::Lerp(StartingPoint,TargetPoint,PathProgress);
		//PathProgress += 0.25 * DeltaTime; 
		PathProgress += 0.1 * DeltaTime; 
		SetActorLocation(CurrentPosition);
	}
	else
	{
		//Once reached the end of the path
		if(PathProgress >= 1)
		{
			AkComponent->Stop();
			//Destroy the vehicle.
			Destroy();
		}
	}

	//If the vehicle has been initialized
	if(VehicleMesh->SkeletalMesh)
	{
		//Check if any characters are in front of vehicle.
		CheckForBlockingPeople();
	}
}

void AVehicle::SetVehicleMesh(USkeletalMesh* MeshToSet, float DistanceToTravel, bool bIsPoliceCar)
{
	//Set the mesh
	VehicleMesh->SetSkeletalMesh(MeshToSet);
	//Target point is set to however many centimeters in ahead the distance to travel is. Use forward vector to make the targetpoint directly ahead.
	TargetPoint = (GetActorLocation() + (GetActorForwardVector() * DistanceToTravel));
	//Starting point is where vehicle is right now.
	StartingPoint = GetActorLocation();
	//Now driving.
	bDriving = true;
	//FAkAudioDevice::Get()->PostEvent("StartCar",this);
	//FAkAudioDevice::Get()->SetSwitch(TEXT("DrivingBraking"),TEXT("Braking"),this);
	//If this is a police car, start the siren.
	if(bIsPoliceCar)
	{
		AkComponent->SetSwitch(nullptr,TEXT("PoliceCar"),TEXT("PoliceCar"));
	}
	//Start the engine sounds
	AkComponent->PostAkEventByName("StartCar");
	//Position the audio component a bit further up to prevent if from being positioned in the floor or anything
	AkComponent->AddRelativeLocation(FVector(0,0,200));
	//Enable occlusion calculations.
	AkComponent->OcclusionRefreshInterval = 0.0f;

}

void AVehicle::SetRtpc(UAkRtpc* RTPCToSet)
{
	RTPC = RTPCToSet;
}

void AVehicle::ResumeDriving()
{
	//if there still isnt an actor in front
	if(!bActorInFront)
	{
		//Resume driving.
		bDriving = true;
		//Start driving sounds again
		AkComponent->SetSwitch(nullptr,TEXT("DrivingBraking"),TEXT("Driving"));
		//Timer no longer active.
		bTimerActive = false;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(Ticker,this,&AVehicle::ResumeDriving,4.0f,false,4.0f);
	}
}


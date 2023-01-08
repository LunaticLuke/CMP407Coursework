// Fill out your copyright notice in the Description page of Project Settings.


#include "FootstepsAnimInstance.h"

#include "AkAudioDevice.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


void UFootstepsAnimInstance::FindFootstepSurface()
{
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;

	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceStart = GetOwningActor()->GetActorLocation();
	FVector TraceEnd = GetOwningActor()->GetActorLocation() + GetOwningActor()->GetActorUpVector() * -200.0f;
	
	// Here we add ourselves to the ignored list so the character won't block the trace.
	//Unreal physical materials are used to determine which surface is being walked on so I have set true that I want information regarding this to be returned from the hit.
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwningActor());
	QueryParams.bReturnPhysicalMaterial = true;
	
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	

	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if(Hit.bBlockingHit)
	{
		//Find out which surface was hit by the line trace.
		const EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());
		
		//Get the name in its pure form. E.g instead of SurfaceType::Concrete it will simply read Concrete.
		const FText SurfaceName = StaticEnum<EPhysicalSurface>()->GetDisplayNameTextByValue(SurfaceType);

		//Convert this to a string.
		FString SurfaceString= SurfaceName.ToString();

		//Pass the surface string through to the Surface switch for this gameobject
		FAkAudioDevice::Get()->SetSwitch(TEXT("Surface"),*SurfaceString,GetOwningActor());
		//Play the corresponding footstep.
		FAkAudioDevice::Get()->PostEvent(FootstepEvent,GetOwningActor());
	}
	
}

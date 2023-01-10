// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FootstepsAnimInstance.generated.h"

class UAkAudioEvent;
/**
 * @brief This class is used within the animation blueprint to check which surfaces the character is walking on. 
 */
UCLASS()
class CMP407LUKEMCFARLANE_API UFootstepsAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	/**
	 * @brief This function determines which surface is being walked on and is called from the ABP_Manny blueprint.
	 */
	UFUNCTION(BlueprintCallable)
		void FindFootstepSurface();
	/**
	 * @brief The footstep event to play
	 */
	UPROPERTY(EditAnywhere)
		UAkAudioEvent* FootstepEvent;
	
	
};

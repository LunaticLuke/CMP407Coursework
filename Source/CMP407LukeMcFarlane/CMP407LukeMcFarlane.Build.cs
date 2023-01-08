// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CMP407LukeMcFarlane : ModuleRules
{
	public CMP407LukeMcFarlane(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AkAudio","PhysicsCore"});
	}
}

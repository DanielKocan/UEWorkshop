// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DaveWorkshopY3A : ModuleRules
{
	public DaveWorkshopY3A(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] { "OmniCameraCore" });
	}
}

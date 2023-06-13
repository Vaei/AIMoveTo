// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AIMoveToEditor : ModuleRules
{
	public AIMoveToEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
		// bUseUnity = false;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"AIMoveTo",
				"AIModule",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"BlueprintGraph",
				"UnrealEd",
			}
			);
	}
}

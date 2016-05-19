// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Fournoid : ModuleRules
{
	public Fournoid(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "OnlineSubsystem", "OnlineSubsystemUtils" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });


        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        {
            DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        }
        PrivateDependencyModuleNames.Add("OnlineSubsystemNull");
    }

}

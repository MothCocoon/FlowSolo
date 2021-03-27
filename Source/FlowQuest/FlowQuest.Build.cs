using UnrealBuildTool;

public class FlowQuest : ModuleRules
{
	public FlowQuest(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Flow"
        });
        
		PrivateDependencyModuleNames.AddRange(new[] 
		{
            "AIModule",
            "Core",
			"CoreUObject",
            "DeveloperSettings",
			"Engine",
            "GameplayTags",
            "Slate",
            "SlateCore",
            "UMG"
        });
    }
}

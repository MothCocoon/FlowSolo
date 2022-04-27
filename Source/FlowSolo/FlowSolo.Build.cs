using UnrealBuildTool;

public class FlowSolo : ModuleRules
{
    public FlowSolo(ReadOnlyTargetRules Target) : base(Target)
    {
        bUseUnity = false;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Flow",
            "FlowQuest"
        });

        PrivateDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "DeveloperSettings",
            "Engine",
            "EnhancedInput",
            "InputCore",
            "Slate",
            "SlateCore",
            "UMG"
        });
    }
}

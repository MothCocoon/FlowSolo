using UnrealBuildTool;

public class FlowQuest : ModuleRules
{
	public FlowQuest(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
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
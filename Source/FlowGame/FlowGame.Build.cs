// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
using UnrealBuildTool;

public class FlowGame : ModuleRules
{
	public FlowGame(ReadOnlyTargetRules target) : base(target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(
		[
			"Flow"
		]);

		PrivateDependencyModuleNames.AddRange(
		[
			"AIModule",
			"Core",
			"CoreUObject",
			"DeveloperSettings",
			"Engine",
			"EnhancedInput",
			"GameplayTags",
			"InputCore",
			"Mover",
			"NavigationSystem",
			"Slate",
			"SlateCore",
			"UMG"
		]);
	}
}
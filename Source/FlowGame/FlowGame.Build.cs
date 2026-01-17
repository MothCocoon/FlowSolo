// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors
using UnrealBuildTool;

public class FlowGame : ModuleRules
{
	public FlowGame(ReadOnlyTargetRules target) : base(target)
	{
		bUseUnity = false;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

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
			"Slate",
			"SlateCore",
			"UMG"
		]);
	}
}
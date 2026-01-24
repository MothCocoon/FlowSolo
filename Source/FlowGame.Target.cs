// Copyright https://github.com/MothCocoon/FlowGame/graphs/contributors

using UnrealBuildTool;

public class FlowGameTarget : TargetRules
{
	public FlowGameTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;

		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		NativePointerMemberBehaviorOverride = PointerMemberBehavior.Disallow;

		ExtraModuleNames.AddRange(
		[
			"FlowGame"
		]);
    }
}

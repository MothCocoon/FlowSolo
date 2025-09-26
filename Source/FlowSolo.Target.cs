// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

using UnrealBuildTool;

public class FlowSoloTarget : TargetRules
{
	public FlowSoloTarget(TargetInfo target) : base(target)
	{
		Type = TargetType.Game;

		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		NativePointerMemberBehaviorOverride = PointerMemberBehavior.Disallow;

		ExtraModuleNames.AddRange(new[]
		{
			"FlowSolo"
		});
	}
}
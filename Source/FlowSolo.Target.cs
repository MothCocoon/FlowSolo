using UnrealBuildTool;

public class FlowSoloTarget : TargetRules
{
	public FlowSoloTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange(new[]
		{ 
			"FlowSolo"
		});

        DefaultBuildSettings = BuildSettingsVersion.V2;
    }
}

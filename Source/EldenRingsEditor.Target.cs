using UnrealBuildTool;
using System.Collections.Generic;

public class EldenRingsTarget : TargetRules
{
    public EldenRingsTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "EldenRings" });
    }
}

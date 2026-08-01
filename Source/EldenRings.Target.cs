using UnrealBuildTool;
using System.Collections.Generic;

public class EldenRingsEditorTarget : TargetRules
{
    public EldenRingsEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

        ExtraModuleNames.AddRange(new string[] { "EldenRings" });
    }
}

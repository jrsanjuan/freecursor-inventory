using UnrealBuildTool;

public class FreeCursor : ModuleRules {
	public FreeCursor(ReadOnlyTargetRules Target) : base(Target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "JsonUtilities" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UMG" });
    }
}

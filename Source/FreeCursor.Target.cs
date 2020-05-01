
using UnrealBuildTool;
using System.Collections.Generic;

public class FreeCursorTarget : TargetRules {
	public FreeCursorTarget(TargetInfo Target) : base(Target) {
		Type = TargetType.Game;
		ExtraModuleNames.AddRange( new string[] { "FreeCursor" } );
	}
}

using UnrealBuildTool;
using System.Collections.Generic;

public class FreeCursorEditorTarget : TargetRules
{
	public FreeCursorEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "FreeCursor" } );
	}
}

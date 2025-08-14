#include "GenericGraphAssetEditor/EditorCommands_GenericGraph.h"

#define LOCTEXT_NAMESPACE "EditorCommands_GenericGraph"

void FEditorCommands_GenericGraph::RegisterCommands()
{
	UI_COMMAND(GraphSettings, "Graph Settings", "Graph Settings", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(AutoArrange, "Auto Arrange", "Auto Arrange", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(Edit, "Edit", "Edit", EUserInterfaceActionType::Button, FInputChord(EKeys::LeftMouseButton, EModifierKey::Control));
}

#undef LOCTEXT_NAMESPACE

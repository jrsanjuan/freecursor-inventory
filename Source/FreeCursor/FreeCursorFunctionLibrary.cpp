#include "FreeCursorFunctionLibrary.h"
#include "FreeAnalogCursor.h"
#include "GameGlobals.h"
#include "model/InventoryModel.h"

//**********************************************************************

void UFreeCursorFunctionLibrary::EnableFreeCursor(class APlayerController* pc) {
	FFreeAnalogCursor::EnableAnalogCursor(pc, TSharedPtr<SWidget>());
}

//**********************************************************************

void UFreeCursorFunctionLibrary::DisableFreeCursor(class APlayerController* pc) {
	FFreeAnalogCursor::DisableAnalogCursor(pc);
}

//**********************************************************************

bool UFreeCursorFunctionLibrary::IsCursorOverInteractableWidget() {
	TSharedPtr<FFreeAnalogCursor> analog = GetDefault<UGameGlobals>()->GetAnalogCursor();
	if (analog.IsValid()) {
		return analog->IsHovered();
	}
	return false;
}

//**********************************************************************

UInventoryModel* UFreeCursorFunctionLibrary::NewInventoryModel() {
	UInventoryModel* NewModel = NewObject<UInventoryModel>();
	NewModel->GenerateInventory();
	return NewModel;
}

//**********************************************************************

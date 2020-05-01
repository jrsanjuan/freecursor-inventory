#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FreeCursorFunctionLibrary.generated.h"

//**********************************************************************
//                       UFreeCursorFunctionLibrary
//**********************************************************************

UCLASS()
class FREECURSOR_API UFreeCursorFunctionLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game")
	static void EnableFreeCursor(class APlayerController* pc);

	UFUNCTION(BlueprintCallable, Category = "Game")
	static void DisableFreeCursor(class APlayerController* pc);

	UFUNCTION(BlueprintPure, Category = "Game")
	static bool IsCursorOverInteractableWidget();

	UFUNCTION(BlueprintCallable, Category = "Game")
	static UInventoryModel* NewInventoryModel();
};

//**********************************************************************

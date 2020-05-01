#pragma once

#include "UMG.h"
#include "AutoPanner.generated.h"

class SAutoPanner;

//**********************************************************************
//                       UAutoPanner
//**********************************************************************

UCLASS()
class UAutoPanner : public UContentWidget {
	GENERATED_BODY()

public:
	UAutoPanner(const FObjectInitializer& objectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Auto Panner")
	FVector2D PaddingScale;
	UFUNCTION(BlueprintCallable, Category = "Auto Panner")
	FVector2D GetNormalizedCursorPosition() const;

	// UWidget
	void SynchronizeProperties() override;
	// UVisual
	void ReleaseSlateResources(bool releaseChildren) override;
	// UObject
	void PostLoad() override;

protected:
	// UPanelWidget
	UClass* GetSlotClass() const override;
	void OnSlotAdded(UPanelSlot* slot) override;
	void OnSlotRemoved(UPanelSlot* slot) override;

	// UWidget
	TSharedRef<SWidget> RebuildWidget() override;

private:
	TSharedPtr<SAutoPanner> mMyAutoPanner;
};

//**********************************************************************

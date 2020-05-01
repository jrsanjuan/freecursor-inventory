#include "AutoPanner.h"
#include "FreeCursor.h"
#include "SAutoPanner.h"

//**********************************************************************

UAutoPanner::UAutoPanner(const FObjectInitializer& ObjectInitializer)
	: UContentWidget(ObjectInitializer) {
}

//**********************************************************************

FVector2D UAutoPanner::GetNormalizedCursorPosition() const {
	return mMyAutoPanner.IsValid() ? mMyAutoPanner->GetNormalizedCursorPosition() : FVector2D::ZeroVector;
}

//**********************************************************************

void UAutoPanner::SynchronizeProperties() {
	Super::SynchronizeProperties();
}

//**********************************************************************

void UAutoPanner::ReleaseSlateResources(bool releaseChildren) {
	Super::ReleaseSlateResources(releaseChildren);
	mMyAutoPanner.Reset();
}

//**********************************************************************

void UAutoPanner::PostLoad() {
	Super::PostLoad();
}

//**********************************************************************

UClass* UAutoPanner::GetSlotClass() const {
	return UPanelSlot::StaticClass();
}

//**********************************************************************

void UAutoPanner::OnSlotAdded(UPanelSlot* slot) {
	if (mMyAutoPanner.IsValid()) {
		mMyAutoPanner->SetContent(slot->Content ? slot->Content->TakeWidget() : SNullWidget::NullWidget);
	}
}

//**********************************************************************

void UAutoPanner::OnSlotRemoved(UPanelSlot* slot) {
	if (mMyAutoPanner.IsValid()) {
		mMyAutoPanner->SetContent(SNullWidget::NullWidget);
	}
}

//**********************************************************************

TSharedRef<SWidget> UAutoPanner::RebuildWidget() {
	if ( GetChildrenCount() > 0 ) {
		UPanelSlot* slot = GetContentSlot();
		if (!IsDesignTime()) {
			mMyAutoPanner = SNew(SAutoPanner).PaddingScale(PaddingScale);
			if (GetChildrenCount() > 0){
				mMyAutoPanner->SetContent(slot->Content ? slot->Content->TakeWidget() : SNullWidget::NullWidget);
			}
			return mMyAutoPanner.ToSharedRef();
		}
		else {
			return SNew(SBox)[slot->Content ? slot->Content->TakeWidget() : SNullWidget::NullWidget];
		}
	}
	return SNullWidget::NullWidget;
}

//**********************************************************************

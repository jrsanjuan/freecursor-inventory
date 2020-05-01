#include "SAutoPanner.h"

//**********************************************************************

void SAutoPanner::Construct(const FArguments& inArgs) {
	mLocalMousePosition = FVector2D::ZeroVector;
	mNormalizedCursorPosition = FVector2D::ZeroVector;
	mPaddingScale = inArgs._PaddingScale;
	this->ChildSlot [inArgs._Content.Widget];
}

//**********************************************************************

void SAutoPanner::OnArrangeChildren(const FGeometry& allottedGeometry, FArrangedChildren& arrangedChildren) const {
	const EVisibility childVisibility = ChildSlot.GetWidget()->GetVisibility();
	if (arrangedChildren.Accepts(childVisibility)) {
		const FVector2D childDesiredSize = (allottedGeometry.Size * mPaddingScale);
		const FVector2D offset = -mLocalMousePosition / allottedGeometry.Size * (childDesiredSize - allottedGeometry.Size);

		arrangedChildren.AddWidget(childVisibility, allottedGeometry.MakeChild(
			ChildSlot.GetWidget(),
			FVector2D(offset.X, offset.Y),
			FVector2D(childDesiredSize)
		));
	}
}

//**********************************************************************

FReply SAutoPanner::OnMouseMove(const FGeometry& myGeometry, const FPointerEvent& mouseEvent) {
	mLocalMousePosition = myGeometry.AbsoluteToLocal(mouseEvent.GetScreenSpacePosition());
	mNormalizedCursorPosition = mLocalMousePosition / myGeometry.Size;
	return FReply::Unhandled();
}

//**********************************************************************

void SAutoPanner::Tick(const FGeometry& allottedGeometry, const double inCurrentTime, const float inDeltaTime) {
	mLocalMousePosition = allottedGeometry.AbsoluteToLocal(FSlateApplicationBase::Get().GetCursorPos());
	mNormalizedCursorPosition = mLocalMousePosition / allottedGeometry.Size;
}

//**********************************************************************

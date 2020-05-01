#pragma once

#include "FreeCursor.h"
#include "SlateBasics.h"

//**********************************************************************
//                       SAutoPanner
//**********************************************************************

class SAutoPanner : public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SAutoPanner) {}
		SLATE_DEFAULT_SLOT(FArguments, Content)
		// The extra size added to the screen.
		SLATE_ARGUMENT(FVector2D, PaddingScale)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	// Widget Interface
	void OnArrangeChildren(const FGeometry& allottedGeometry, FArrangedChildren& arrangedChildren) const override;
	virtual FReply OnMouseMove(const FGeometry& myGeometry, const FPointerEvent& mouseEvent) override;
	virtual void Tick(const FGeometry& allottedGeometry, const double inCurrentTime, const float inDeltaTime) override;

	void SetContent(const TSharedRef<SWidget>& inContent) { this->ChildSlot[inContent]; }
	FVector2D GetNormalizedCursorPosition() const { return mNormalizedCursorPosition; }

	void SetPaddingScale(FVector2D inPaddingScale) { mPaddingScale = inPaddingScale; }
	FVector2D GetPaddingScale() const { return mPaddingScale; }

private:
	FVector2D mLocalMousePosition;
	FVector2D mNormalizedCursorPosition;
	FVector2D mPaddingScale;
};

//**********************************************************************

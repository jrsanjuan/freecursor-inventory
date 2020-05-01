#pragma once

#include "AnalogCursor.h"
#include <Engine.h>

//**********************************************************************
//                       FFreeAnalogCursor
//**********************************************************************

class FFreeAnalogCursor : public FAnalogCursor {
public:
	FFreeAnalogCursor(class APlayerController* pc, float radius);
	~FFreeAnalogCursor() = default;

	FREECURSOR_API static void EnableAnalogCursor(class APlayerController* pc, TSharedPtr<SWidget> widgetToFocus);
	FREECURSOR_API static void DisableAnalogCursor(class APlayerController* pc);

	void Tick(const float deltaTime, FSlateApplication& slateApp, TSharedRef<ICursor> cursor) override;

	FORCEINLINE FName GetHoveredWidgetName() const {
		return mHoveredWidgetName;
	}

	FORCEINLINE bool IsHovered() const {
		return mHoveredWidgetName != NAME_None;
	}

	FORCEINLINE FVector2D GetCurrentPosition() const {
		return mCurrentPosition;
	}

	FORCEINLINE FVector2D GetVelocity() const {
		return mVelocity;
	}

	FORCEINLINE bool GetIsUsingAnalogCursor() const {
		return mIsUsingAnalogCursor;
	}

	FORCEINLINE FVector2D GetLastCursorDirection() const {
		return mLastCursorDirection;
	}

	FORCEINLINE float GetRadius() const	{
		return mRadius;
	}

private:
	FVector2D GetAnalogCursorAccelerationValue(const FVector2D& analogValues, float dpiScale);
	bool IsWidgetInteractable(const TSharedPtr<SWidget> widget);

	FVector2D mVelocity;
	FVector2D mCurrentPosition;
	FVector2D mLastCursorDirection;
	FName mHoveredWidgetName;
	bool mIsUsingAnalogCursor;
	float mRadius;
	FLocalPlayerContext mPlayerContext;
	static TSharedPtr<FFreeAnalogCursor> mFreeAnalogCursor;
};

//**********************************************************************

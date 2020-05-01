#include "FreeAnalogCursor.h"
#include "FreeCursor.h"
#include "GameGlobals.h"
#include "WidgetLayoutLibrary.h"
#include "Engine/UserInterfaceSettings.h"

TSharedPtr<FFreeAnalogCursor> FFreeAnalogCursor::mFreeAnalogCursor;

//**********************************************************************

FFreeAnalogCursor::FFreeAnalogCursor(class APlayerController* pc, float radius)
	: mVelocity(FVector2D::ZeroVector)
	, mCurrentPosition(FLT_MAX, FLT_MAX)
	, mLastCursorDirection(FVector2D::ZeroVector)
	, mHoveredWidgetName(NAME_None)
	, mIsUsingAnalogCursor(false)
	, mRadius(FMath::Max<float>(radius, 16.0f))
	, mPlayerContext(pc) {
}

//**********************************************************************

void FFreeAnalogCursor::EnableAnalogCursor(class APlayerController* pc, TSharedPtr<SWidget> widgetToFocus) {
	if (pc) {
		const float cursorRadius = GetDefault<UGameGlobals>()->GetAnalogCursorRadius();
		mFreeAnalogCursor = MakeShareable(new FFreeAnalogCursor(pc, cursorRadius));
		FSlateApplication::Get().RegisterInputPreProcessor(mFreeAnalogCursor);
		FSlateApplication::Get().SetCursorRadius(cursorRadius);

		GetMutableDefault<UGameGlobals>()->SetAnalogCursor(mFreeAnalogCursor);
		FInputModeGameAndUI newInputMode;
		newInputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		newInputMode.SetWidgetToFocus(widgetToFocus);
		pc->SetInputMode(newInputMode);
	}
}

//**********************************************************************

void FFreeAnalogCursor::DisableAnalogCursor(class APlayerController* pc) {
	if (pc) {
		if (FSlateApplication::IsInitialized()) {
			FSlateApplication::Get().UnregisterInputPreProcessor(mFreeAnalogCursor);
			FSlateApplication::Get().SetCursorRadius(0.0f);
		}
		FInputModeGameOnly NewInputMode;
		pc->SetInputMode(NewInputMode);
	}
}

//**********************************************************************

void FFreeAnalogCursor::Tick(const float deltaTime, FSlateApplication& slateApp, TSharedRef<ICursor> cursor) {
	if (mPlayerContext.IsValid()) {
		const FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(mPlayerContext.GetPlayerController());
		const float dpiScale = GetDefault<UUserInterfaceSettings>()->GetDPIScaleBasedOnSize(FIntPoint(FMath::RoundToInt(viewportSize.X), FMath::RoundToInt(viewportSize.Y)));
		const UGameGlobals* settings = GetDefault<UGameGlobals>();

		if (settings->GetUseEngineAnalogCursor()) {
			FAnalogCursor::Tick(deltaTime, slateApp, cursor);
			return;
		}
		const FVector2D currentPositionTruc = FVector2D(FMath::TruncToFloat(mCurrentPosition.X), FMath::TruncToFloat(mCurrentPosition.Y));
		if (currentPositionTruc != cursor->GetPosition()) {
			mCurrentPosition = cursor->GetPosition();
			mVelocity = FVector2D::ZeroVector;
			mLastCursorDirection = FVector2D::ZeroVector;
			mIsUsingAnalogCursor = false;
			FSlateApplication::Get().SetCursorRadius(0.0f);
		}

		const FVector2D oldPosition = mCurrentPosition;
		const float maxSpeedNoHover = settings->GetMaxAnalogCursorSpeed() * dpiScale;
		const float maxSpeedHover = settings->GetMaxAnalogCursorSpeedWhenHovered() * dpiScale;
		const float dragCoNoHover = settings->GetAnalogCursorDragCoefficient() * dpiScale;
		const float dragCoHovered = settings->GetAnalogCursorDragCoefficientWhenHovered() * dpiScale;
		const float minCursorSpeed = settings->GetMinAnalogCursorSpeed() * dpiScale;

		mHoveredWidgetName = NAME_None;
		float dragCo = dragCoNoHover;
		float maxSpeed = maxSpeedNoHover;

		FWidgetPath widgetPath = slateApp.LocateWindowUnderMouse(oldPosition, slateApp.GetInteractiveTopLevelWindows());
		if (widgetPath.IsValid()) {
			for (int32 i = widgetPath.Widgets.Num() - 1; i >= 0; --i) {
				FArrangedWidget& arrangedWidget = widgetPath.Widgets[i];
				TSharedRef<SWidget> widget = arrangedWidget.Widget;
				if (IsWidgetInteractable(widget)) {
					mHoveredWidgetName = widget->GetType();
					dragCo = dragCoHovered;
					maxSpeed = maxSpeedHover;
					break;
				}
			}
		}

		const FVector2D accelFromAnalogStick = GetAnalogCursorAccelerationValue(GetAnalogValues(), dpiScale);
		FVector2D NewAccelerationThisFrame = FVector2D::ZeroVector;
		if (!settings->GetAnalogCursorNoAcceleration()) {
			if (!accelFromAnalogStick.IsZero() || !mVelocity.IsZero()) {
				const FVector2D A1 = (accelFromAnalogStick - (dragCo * mVelocity)) * deltaTime;
				const FVector2D A2 = (accelFromAnalogStick - (dragCo * (mVelocity + (A1 * 0.5f)))) * deltaTime;
				const FVector2D A3 = (accelFromAnalogStick - (dragCo * (mVelocity + (A2 * 0.5f)))) * deltaTime;
				const FVector2D A4 = (accelFromAnalogStick - (dragCo * (mVelocity + A3))) * deltaTime;
				NewAccelerationThisFrame = (A1 + (2.0f * A2) + (2.0f * A3) + A4) / 6.0f;
				mVelocity += NewAccelerationThisFrame;
			}
		} else {
			mVelocity = accelFromAnalogStick;
		}

		const float velSizeSq = mVelocity.SizeSquared();
		if (velSizeSq < (minCursorSpeed * minCursorSpeed)) {
			mVelocity = FVector2D::ZeroVector;
		} else if (velSizeSq > (maxSpeed * maxSpeed)) {
			mVelocity = mVelocity.GetSafeNormal() * maxSpeed;
		}

		if (!mVelocity.IsZero()) {
			mLastCursorDirection = mVelocity.GetSafeNormal();
		}

		mCurrentPosition += (mVelocity * deltaTime);
		UpdateCursorPosition(slateApp, cursor, mCurrentPosition);
		if (!accelFromAnalogStick.IsZero()) {
			mIsUsingAnalogCursor = true;
			FSlateApplication::Get().SetCursorRadius(settings->GetAnalogCursorRadius() * dpiScale);
		}
	}
}

//**********************************************************************

FVector2D FFreeAnalogCursor::GetAnalogCursorAccelerationValue(const FVector2D& analogValues, float dpiScale) {
	const UGameGlobals* settings = GetDefault<UGameGlobals>();

	FVector2D retValue = FVector2D::ZeroVector;
	if (const FRichCurve* accelerationCurve = settings->GetAnalogCursorAccelerationCurve()) {
		const float deadZoneSize = settings->GetAnalogCursorDeadZone();
		const float analogValSize = analogValues.Size();
		if (analogValSize > deadZoneSize) {
			retValue = accelerationCurve->Eval(analogValSize) * analogValues.GetSafeNormal() * dpiScale;
			retValue *= settings->GetAnalogCursorAccelerationMultiplier() * dpiScale;
		}
	}
	return retValue;
}

//**********************************************************************

bool FFreeAnalogCursor::IsWidgetInteractable(const TSharedPtr<SWidget> widget) {
	return widget.IsValid() && widget->IsInteractable();
}

//**********************************************************************

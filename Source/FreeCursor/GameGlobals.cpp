#include "GameGlobals.h"
#include "FreeCursor.h"

//**********************************************************************

UGameGlobals::UGameGlobals(const FObjectInitializer& objectInitializer)
	: UDeveloperSettings(objectInitializer)
	, mMaxAnalogCursorSpeed(1300.0f)
	, mMaxAnalogCursorSpeedWhenHovered(650.0f)
	, mAnalogCursorDragCoefficient(8.0f)
	, mAnalogCursorDragCoefficientWhenHovered(14.0f)
	, mMinAnalogCursorSpeed(5.0f)
	, mAnalogCursorDeadZone(0.15f)
	, mAnalogCursorAccelerationMultiplier(9000.0f)
	, mAnalogCursorSize(40.0f) {
	mAnalogCursorAccelerationCurve.EditorCurveData.AddKey(0, 0);
	mAnalogCursorAccelerationCurve.EditorCurveData.AddKey(1, 1);
}

//**********************************************************************

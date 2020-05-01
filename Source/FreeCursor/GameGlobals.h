#pragma once

#include "Engine/DeveloperSettings.h"
#include "GameGlobals.generated.h"

class FFreeAnalogCursor;

//**********************************************************************
//                       UGameGlobals
//**********************************************************************

UCLASS(config=Game, defaultconfig)
class FREECURSOR_API UGameGlobals : public UDeveloperSettings {
	GENERATED_BODY()

public:
	UGameGlobals(const FObjectInitializer& objectInitializer);

	FORCEINLINE const FRichCurve* GetAnalogCursorAccelerationCurve() const {
		return mAnalogCursorAccelerationCurve.GetRichCurveConst();
	}
	
	FORCEINLINE float GetMaxAnalogCursorSpeed() const {
		return mMaxAnalogCursorSpeed;
	}

	FORCEINLINE float GetMaxAnalogCursorSpeedWhenHovered() const {
		return mMaxAnalogCursorSpeedWhenHovered;
	}

	FORCEINLINE float GetAnalogCursorDragCoefficient() const {
		return FMath::Min<float>(mAnalogCursorDragCoefficientWhenHovered, mAnalogCursorDragCoefficient);
	}

	FORCEINLINE float GetAnalogCursorDragCoefficientWhenHovered() const {
		return FMath::Max<float>(mAnalogCursorDragCoefficientWhenHovered, mAnalogCursorDragCoefficient);
	}

	FORCEINLINE float GetMinAnalogCursorSpeed() const {
		return mMinAnalogCursorSpeed;
	}

	FORCEINLINE float GetAnalogCursorAccelerationMultiplier() const {
		return mAnalogCursorAccelerationMultiplier;
	}

	FORCEINLINE float GetAnalogCursorDeadZone() const {
		return mAnalogCursorDeadZone;
	}

	FORCEINLINE float GetAnalogCursorSize() const {
		return FMath::Max<float>(mAnalogCursorSize, 1.0f);
	}

	FORCEINLINE FVector2D GetAnalogCursorSizeVector() const {
		return FVector2D(GetAnalogCursorSize(), GetAnalogCursorSize());
	}

	FORCEINLINE float GetAnalogCursorRadius() const {
		return GetAnalogCursorSize() / 2.0f;
	}

	FORCEINLINE bool GetUseEngineAnalogCursor() const {
		return mUseEngineAnalogCursor;
	}

	FORCEINLINE bool GetAnalogCursorNoAcceleration() const {
		return mAnalogCursorNoAcceleration;
	}

	FORCEINLINE void SetAnalogCursor(TSharedPtr<FFreeAnalogCursor> inAnalogCursor) {
		mAnalogCursor = inAnalogCursor;
	}

	FORCEINLINE TSharedPtr<FFreeAnalogCursor> GetAnalogCursor() const {
		return mAnalogCursor.Pin();
	}

private:
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta=(XAxisName="Strength", YAxisName="Acceleration" ))
	FRuntimeFloatCurve mAnalogCursorAccelerationCurve;

	// The max speed of the Analog Cursor
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0"))
	float mMaxAnalogCursorSpeed;

	// The max speed of the Analog Cursor when hovering over a widget that is interactable
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0"))
	float mMaxAnalogCursorSpeedWhenHovered;

	// The coefficient of drag applied to the cursor
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "0.0"))
	float mAnalogCursorDragCoefficient;

	// The coefficient of drag applied to the cursor when hovering
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "0.0"))
	float mAnalogCursorDragCoefficientWhenHovered;

	// The min speed of the analog cursor. If it goes below this value, the speed is set to 0.
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "0.0"))
	float mMinAnalogCursorSpeed;

	// Deadzone value for input from the analog stick
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float mAnalogCursorDeadZone;

	// Multiplied by the value spit out by the normalized acceleration curve
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0"))
	float mAnalogCursorAccelerationMultiplier;

	// The size (on screen) of the analog cursor
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor", meta = (ClampMin = "1.0", ClampMax = "128.0"))
	float mAnalogCursorSize;

	// If true, defaults to the Engine's Analog Cursor
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor")
	bool mUseEngineAnalogCursor;

	// If True, AnalogCursorAccelerationCurve will be used as a Velocity Curve
	UPROPERTY(config, EditAnywhere, Category = "Analog Cursor")
	bool mAnalogCursorNoAcceleration;

	// Analog Cursor
	TWeakPtr<FFreeAnalogCursor> mAnalogCursor;
};
#pragma once

#include "InventoryItem.generated.h"

//**********************************************************************
//                       UInventoryItem
//**********************************************************************

UCLASS(BlueprintType)
class UInventoryItem : public UObject {
	GENERATED_BODY()

public:
	UInventoryItem(const FObjectInitializer& ObjectInitializer);

	void InitItem(
		FString iconPath,
		FString name,
		FString type,
		FString rarity,
		int32 level,
		int32 power,
		FString flavor,
		float rateFire,
		float impact,
		float range
	);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	FText NameText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	FText TypeText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	int32 RequiredLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	FText FlavorText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	FText Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	float RateFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	float Impact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryItem")
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "InventoryItem")
	UTexture2D* IconTexture;

	UFUNCTION(BlueprintCallable, Category = "InventoryItem")
	FLinearColor GetRarityColor() const;
};

//**********************************************************************

#include "InventoryItem.h"
#include "FreeCursor.h"

//**********************************************************************

UInventoryItem::UInventoryItem(const FObjectInitializer& ObjectInitializer)
	: UObject(ObjectInitializer) {
}

//**********************************************************************

void UInventoryItem::InitItem(
	FString iconPath,
	FString name,
	FString type,
	FString rarity,
	int32 level,
	int32 power,
	FString flavor,
	float rateFire,
	float impact,
	float range) {
	IconTexture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *iconPath));
	NameText = FText::FromString(name);
	TypeText = FText::FromString(type);
	Rarity = FText::FromString(rarity);
	RequiredLevel = level;
	Damage = power;
	FlavorText = FText::FromString(flavor);
	RateFire = rateFire / 100.f;
	Impact = impact / 100.f;
	Range = range / 100.f;
}

//**********************************************************************

FLinearColor UInventoryItem::GetRarityColor() const {
	if (Rarity.ToString() == "Common") {
		return FLinearColor(0.3, 0.3, 0.3);
	} else if (Rarity.ToString() == "Uncommon") {
		return FLinearColor(0, 0.3, 0);
	} else if (Rarity.ToString() == "Rare") {
		return FLinearColor(0, 0.065, 1);
	} else if (Rarity.ToString() == "Legendary") {
		return FLinearColor(0.4, 0.0, 1);
	} else if (Rarity.ToString() == "Exotic") {
		return FLinearColor(1, 0.248, 0);
	}
	return FLinearColor(1, 1, 1);
}

//**********************************************************************

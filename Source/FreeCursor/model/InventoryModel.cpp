#include "InventoryModel.h"
#include "InventoryItem.h"
#include "FreeCursor.h"

const FString kJsonPath("UI/Data/inventory.json");
const FString kJsonRootField("InventoryItems");

//**********************************************************************

UInventoryModel::UInventoryModel(const FObjectInitializer& ObjectInitializer)
	: UObject(ObjectInitializer) {
}

//**********************************************************************

void UInventoryModel::GenerateInventory() {
	FString jsonStr;
	FString fullPath = FPaths::ProjectContentDir();
	fullPath += kJsonPath;
	FFileHelper::LoadFileToString(jsonStr, *fullPath);

	TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(jsonStr);
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(jsonReader, jsonObject) && jsonObject.IsValid()) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("JSON deserialize worked!"));
		}
		CreateItems(jsonObject->GetArrayField(kJsonRootField));
	} else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not able to deserialize JSON"));
		}
	}
}

//**********************************************************************

void UInventoryModel::CreateItems(const TArray<TSharedPtr<FJsonValue>>& objects) {
	for (int32 i = 0; i < objects.Num(); i++) {
		TSharedPtr<FJsonObject> json = objects[i]->AsObject();
		Items.Add(NewObject<UInventoryItem>());
		Items[i]->InitItem(
			json->GetStringField(TEXT("IconPath")),
			json->GetStringField(TEXT("Name")),
			json->GetStringField(TEXT("Type")),
			json->GetStringField(TEXT("Rarity")),
			json->GetNumberField(TEXT("Level")),
			json->GetNumberField(TEXT("Power")),
			json->GetStringField(TEXT("Flavor")),
			json->GetNumberField(TEXT("RateFire")),
			json->GetNumberField(TEXT("Impact")),
			json->GetNumberField(TEXT("Range"))
		);
	}
}

//**********************************************************************

#pragma once

#include "InventoryModel.generated.h"

class UInventoryItem;

//**********************************************************************
//                       UInventoryModel
//**********************************************************************

UCLASS(BlueprintType)
class UInventoryModel : public UObject {
	GENERATED_BODY()

public:
	UInventoryModel(const FObjectInitializer& objectInitializer);

	void GenerateInventory();
	const TArray<UInventoryItem*>& GetItems() const { return Items; }

protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="InventoryModel")
		TArray<UInventoryItem*> Items;

private:
	void CreateItems(const TArray<TSharedPtr<FJsonValue>>& objects);
};

//**********************************************************************

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SkillListViewWidget.generated.h"

class USkillData;
class UImage;
class UTextBlock;
class UButton;
class USkillSlotWidget;

UCLASS()
class SWORDOFVENGEANCE_API USkillListViewWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

	//virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	//virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	//virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

private:

	//TSubclassOf<USkillData> SkillDataClass;
	UPROPERTY()
	USkillData* SkillData;

private:

	
	UPROPERTY(meta = (BindWidget))
	USkillSlotWidget* SkillSlotWidget;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDesc;

	

public:

	UFUNCTION()
	void SkillIconButtonClicked();
};

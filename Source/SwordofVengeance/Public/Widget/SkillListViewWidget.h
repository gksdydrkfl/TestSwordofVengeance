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

UCLASS()
class SWORDOFVENGEANCE_API USkillListViewWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;

private:

	//TSubclassOf<USkillData> SkillDataClass;
	UPROPERTY()
	USkillData* SkillData;

private:

	UPROPERTY(meta = (BindWidget))
	UImage* SkillIcon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SkillDesc;

	UPROPERTY(meta = (BindWidget))
	UButton* SkillIconButton;

public:

	UFUNCTION()
	void SkillIconButtonClicked();
};

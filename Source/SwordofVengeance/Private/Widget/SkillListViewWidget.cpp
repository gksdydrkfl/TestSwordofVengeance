// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListViewWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SwordofVengeance/DebugMacro.h"
#include "DataAsset/SkillData.h"
#include "Components/Button.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/SkillSlotWidget.h"

void USkillListViewWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillListViewWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
	SkillData = Cast<USkillData>(ListItemObject);
	if (SkillData)
	{
		UTexture2D* NewSkillIcon = SkillData->SkillIcon;

		FText NewSkillDesc = FText::FromName(SkillData->SkillDesc);

		if (NewSkillIcon)
		{
			if (SkillSlotWidget)
			{
				SkillSlotWidget->SetImage(NewSkillIcon);

				SkillSlotWidget->SetSlotIndex(SkillData->SlotIndex);
			}
		}

		SkillDesc->SetText(NewSkillDesc);
	}

}

void USkillListViewWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
}

void USkillListViewWidget::SkillIconButtonClicked()
{
	Debug::Log("Button Clicked");
}

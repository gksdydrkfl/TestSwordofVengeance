// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListViewWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SwordofVengeance/DebugMacro.h"
#include "DataAsset/SkillData.h"

void USkillListViewWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	
	SkillData = Cast<USkillData>(ListItemObject);
	if (SkillData)
	{
		UTexture2D* NewSkillIcon = SkillData->SkillIcon;

		FText NewSkillDesc = FText::FromName(SkillData->SkillDesc);

		if (NewSkillIcon)
		{
			SkillIcon->SetBrushFromTexture(NewSkillIcon);
		}

		SkillDesc->SetText(NewSkillDesc);
	}

}

void USkillListViewWidget::NativeOnItemSelectionChanged(bool bIsSelected)
{
}

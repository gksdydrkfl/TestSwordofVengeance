// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillBarWidget.h"
#include "Widget/SkillSlotWidget.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Components/UniformGridPanel.h"
#include "DataAsset/SkillData.h"

//bool USkillBarWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
//{
//	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
//
//	USkillSlotDragWidget* SkillSlotDragWidget = Cast<USkillSlotDragWidget>(InOperation);
//
//	if (SkillSlotDragWidget == nullptr)
//	{
//		return;
//	}
//
//	Debug::Log("Test");
//}

void USkillBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (SkillSlotGrid == nullptr)
	{
		return;
	}

	for (int32 i = 0; i < 5; ++i)
	{
		UWidget* Widget = SkillSlotGrid->GetChildAt(i);
		if (Widget)
		{
			USkillSlotWidget* SkillSlotWidget = Cast<USkillSlotWidget>(Widget);
			if (SkillSlotWidget)
			{
				SkillSlotWidget->SetImage(TransparentTexture);
				SkillSlotWidget->SetParentWidget(this);
				SkillSlotWidget->SetSlotIndex(i);
			}
		}
	}

}

void USkillBarWidget::SerachOvelapSkill(const FName& SerachName, const int32& Index)
{
	for (int32 i = 0; i < 5; ++i)
	{
		if (i == Index)
		{
			continue;
		}
		UWidget* Widget = SkillSlotGrid->GetChildAt(i);

		if (Widget == nullptr)
		{
			return;
		}

		USkillSlotWidget* SkillSlotWidget = Cast<USkillSlotWidget>(Widget);

		if (SkillSlotWidget)
		{
			if (SkillSlotWidget->GetSkillData()== nullptr)
			{
				continue;
			}
			FName SkillName = SkillSlotWidget->GetSkillData()->GetSkillName();

			if (SkillName == SerachName)
			{
				SkillSlotWidget->SetImage(TransparentTexture);
			}
		}
	}
}
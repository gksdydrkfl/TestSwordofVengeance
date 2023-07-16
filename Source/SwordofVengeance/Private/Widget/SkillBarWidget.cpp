// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillBarWidget.h"
#include "Widget/SkillSlotWidget.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Components/UniformGridPanel.h"
#include "DataAsset/SkillData.h"
#include "SwordofVengeance/DebugMacro.h"
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

void USkillBarWidget::SearchOvelapSkill(const FName& SearchName, const int32& Index)
{
	USkillSlotWidget* SkillSlotWidget = SearchSkill(SearchName, Index);
	if (SkillSlotWidget)
	{
		SkillSlotWidget->SetImage(TransparentTexture);
		//SkillSlotWidget->
		SkillSlotWidget->SetText(FName(" "));
	}

}

USkillSlotWidget* USkillBarWidget::SearchSkill(const FName& SearchName, const int32& Index, const bool& bComboCheck)
{
	for (int32 i = 0; i < 5; ++i)
	{
		if (bComboCheck == false)
		{
			if (i == Index)
			{
				continue;
			}
		}

		UWidget* Widget = SkillSlotGrid->GetChildAt(i);

		if (Widget == nullptr)
		{
			return nullptr;
		}

		USkillSlotWidget* SkillSlotWidget = Cast<USkillSlotWidget>(Widget);

		if (SkillSlotWidget)
		{
			if (SkillSlotWidget->GetSkillData() == nullptr)
			{
				continue;
			}
			FName SkillName = SkillSlotWidget->GetSkillData()->GetSkillName();

			if (SkillName == SearchName)
			{
				return SkillSlotWidget;
			}
		}
	}
	Debug::Log("NotSkill");
	return nullptr;
}

void USkillBarWidget::UpdateSkillBar(const ESkillType& SearchName, int32 Index)
{
	Debug::Log(Index);

	switch (SearchName)
	{
	case ESkillType::EST_KatanaBaseAttack:
		USkillSlotWidget* SkillSlotWidget = SearchSkill(FName("ComboAttack"), 0, true);
		if (SkillSlotWidget)
		{
			if (Index == 3)
			{
				Index = 0;
			}
			USkillData* SkillData = SkillSlotWidget->GetSkillData()->List[Index];
			UTexture2D* Texture = SkillData->GetTexture();
			if (Texture)
			{
				SkillSlotWidget->SetImage(Texture);
			}
		}
		//SkillSlotWidget

		break;
	//case ESkillType::EST_KatanaBattojutsu:

	//	break;
	}


}
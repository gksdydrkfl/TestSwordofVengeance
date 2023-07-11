// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillBarWidget.h"
#include "Widget/SkillSlotWidget.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Components/UniformGridPanel.h"
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
	//if (SkillSlotGrid == nullptr)
	//{
	//	return;
	//}

	//for (int32 i = 0; i < 5; ++i)
	//{
	//	UWidget* Widget = SkillSlotGrid->GetChildAt(i);
	//	if (Widget)
	//	{
	//		USkillSlotWidget* SkillSlotWidgetCast = Cast<USkillSlotWidget>(Widget);
	//		if (SkillSlotWidgetCast)
	//		{
	//			SkillSlotWidgetCast->SetSkillWidgetType()
	//		}
	//	}
	//}
}

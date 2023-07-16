// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillSlotWidget.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/SkillSlotDragWidget.h"
#include "Widget/SkillBarWidget.h"
#include "DataAsset/SkillData.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

FEventReply USkillSlotWidget::RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	return reply;
}

FReply USkillSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);


	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

FReply USkillSlotWidget::CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey)
{
	if (InMouseEvent.GetEffectingButton() == DragKey)
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();

		if (WidgetDetectingDrag)
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if (SlateWidgetDetectingDrag.IsValid())
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}

	return FReply::Unhandled();
}


void USkillSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (SkillData)
	{
		bool bActive = SkillData->GetSkillActive();
		if (bActive == false)
		{
			return;

		}
	}
	else
	{
		return;
	}


	USkillSlotDragWidget* Operation = NewObject<USkillSlotDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	Operation->WidgetReference = this;
	Operation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	Operation->DefaultDragVisual = this;

	OutOperation = Operation;
}

bool USkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillSlotDragWidget* Operation = Cast<USkillSlotDragWidget>(InOperation);

	USkillSlotWidget* SkillSlotWidget = Cast<USkillSlotWidget>(Operation->WidgetReference);

	//USkillData* TempSkillData = SkillData;

	//SkillData = SkillSlotWidget->GetSkillData();

	bool bEquipSkill = EquipSkill(SkillSlotWidget);

	SkillSlotWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	if (SkillData)
	{
		SetText(SkillData->SkillName);
	}

	if (SkillSlotWidget->SkillData)
	{
		SkillSlotWidget->SetText(SkillData->SkillName);
	}
	else
	{
		SkillSlotWidget->SetText(FName(" "));
	}

	return bEquipSkill ? true : false;

	//return Operation ? true : false;
}

void USkillSlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//RemoveFromParent();

}

bool USkillSlotWidget::EquipSkill(USkillSlotWidget* Widget)
{
	switch (Widget->SkillWidgetType)
	{
	case ESkillSlotTypeWidget::ESSTW_SkillBar:

		Swap(Widget);

		return true;

	case ESkillSlotTypeWidget::ESSTW_SkillWindow:

		if (ESkillSlotTypeWidget::ESSTW_SkillWindow == SkillWidgetType)
		{
			return false;
		}

		SkillData = Widget->GetSkillData();

		USkillBarWidget* SkillBarWidget = Cast<USkillBarWidget>(ParentWidget);

		if (SkillBarWidget)
		{
			if (SkillData)
			{
				FName Name = SkillData->GetSkillName();

				SkillBarWidget->SearchOvelapSkill(Name, SlotIndex);
			}
			SetImage(Widget->GetTexture());

		}
		return true;
	}
	return true;
}

void USkillSlotWidget::SetImage(UTexture2D* NewTexture)
{
	if (NewTexture)
	{
		SkillIcon->SetBrushFromTexture(NewTexture);
		SkillIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		SkillIcon->SetBrushSize(FVector2D(60.f, 60.f));
		Texture = NewTexture;
	}
}

void USkillSlotWidget::Swap(USkillSlotWidget* Widget)
{
	UTexture2D* TempTexture = Widget->GetTexture();
	USkillData* Data = Widget->GetSkillData();

	Widget->SetImage(Texture);
	Widget->SetSkillData(SkillData);

	SetImage(TempTexture);
	SetSkillData(Data);
	this->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	Widget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USkillSlotWidget::SetText(FName Name)
{
	SkillName->SetText(FText::FromName(Name));
}
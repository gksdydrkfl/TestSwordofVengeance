// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillSlotWidget.h"
#include "Components/Image.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/SkillSlotDragWidget.h"

void USkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SkillIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
}

FReply USkillSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);


	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

FReply USkillSlotWidget::CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey)
{
	if (InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/)
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

	USkillSlotDragWidget* Operation = NewObject<USkillSlotDragWidget>();
	this->SetVisibility(ESlateVisibility::HitTestInvisible);

	Operation->WidgetReference = this;
	Operation->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	Operation->Pivot = EDragPivot::MouseDown;
	Operation->DefaultDragVisual = this;
	

	OutOperation = Operation;
}

bool USkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USkillSlotDragWidget* Operation = Cast<USkillSlotDragWidget>(InOperation);

	Debug::Log("Dragggggggggg");

	return Operation ? true : false;
}


void USkillSlotWidget::SetImage(UTexture2D* NewTexture)
{
	if (NewTexture)
	{
		if (SkillIcon)
		{
			SkillIcon->SetBrushFromTexture(NewTexture);
			SkillIcon->SetBrushSize(FVector2D(70.f, 70.f));
			SkillIcon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		}
	}
}


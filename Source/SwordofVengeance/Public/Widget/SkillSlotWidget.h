// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotTypeWidget.h"
#include "SkillSlotWidget.generated.h"

class UImage;
class UTexture2D;

UCLASS()
class SWORDOFVENGEANCE_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	UPROPERTY(meta = (BindWidget))
	UImage* SkillIcon;

	int32 SlotIndex;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	ESkillSlotTypeWidget SkillWidgetType;

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey);


public:

	FORCEINLINE void SetSlotIndex(const int32& NewIndex) { SlotIndex = NewIndex; };
	FORCEINLINE void SetSkillWidgetType(const ESkillSlotTypeWidget& NewSkillSlotTypeWidget) { SkillWidgetType = NewSkillSlotTypeWidget; };

	void SetImage(UTexture2D* NewTexture);

};

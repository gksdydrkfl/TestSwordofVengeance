// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotTypeWidget.h"
#include "SkillSlotWidget.generated.h"

class UImage;
class UTexture2D;
class USkillData;
class UButton;

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

	UUserWidget* ParentWidget;

	UTexture2D* Texture;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UTexture2D* TransparentTexture;

	USkillData* SkillData;

	UPROPERTY(meta = (BindWidget))
	UButton* SkillButton;
public:

	UFUNCTION(BlueprintCallable)
	FEventReply RedirectMouseDownToWidget(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey);


public:

	FORCEINLINE void SetSlotIndex(const int32& NewIndex) { SlotIndex = NewIndex; };
	FORCEINLINE void SetSkillWidgetType(const ESkillSlotTypeWidget& NewSkillSlotTypeWidget) { SkillWidgetType = NewSkillSlotTypeWidget; };
	FORCEINLINE UTexture2D* GetTexture() {return Texture; };
	FORCEINLINE void SetParentWidget(UUserWidget* NewParentWidget) { ParentWidget = NewParentWidget; };
	FORCEINLINE void SetSkillData(USkillData* Data) { SkillData = Data; };
	FORCEINLINE USkillData* GetSkillData() const { return SkillData; };

	void EquipSkill(USkillSlotWidget* Widget);

	void SetImage(UTexture2D* NewTexture);

	void Swap(USkillSlotWidget* Widget);

};

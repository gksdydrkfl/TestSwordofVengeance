// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSystem/Skill/SkillType.h"
#include "SkillBarWidget.generated.h"

class UUniformGridPanel;
class USkillSlotWidget;

UCLASS()
class SWORDOFVENGEANCE_API USkillBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SkillSlotGrid;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UTexture2D* TransparentTexture;

public:

	USkillSlotWidget* SearchSkill(const FName& SearchName, const int32& Index = 0, const bool& bComboCheck = false);

	void SearchOvelapSkill(const FName& SearchName, const int32& Index);

	void UpdateSkillBar(const ESkillType& SearchName, int32 Index = 0);

};

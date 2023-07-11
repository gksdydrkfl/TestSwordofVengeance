// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillBarWidget.generated.h"

class UUniformGridPanel;

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

public:

};

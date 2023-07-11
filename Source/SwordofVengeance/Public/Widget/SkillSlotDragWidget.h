// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "SkillSlotTypeWidget.h"
#include "SkillSlotDragWidget.generated.h"




UCLASS()
class SWORDOFVENGEANCE_API USkillSlotDragWidget : public UDragDropOperation
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillSlotTypeWidget SkillWidgetType;
};

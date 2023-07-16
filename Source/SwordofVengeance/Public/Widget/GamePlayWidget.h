// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GamePlayWidget.generated.h"

class USkillBarWidget;

UCLASS()
class SWORDOFVENGEANCE_API UGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	USkillBarWidget* SkillBar;

public:

	FORCEINLINE USkillBarWidget* GetSkillBarWidget() const { return SkillBar; };
};

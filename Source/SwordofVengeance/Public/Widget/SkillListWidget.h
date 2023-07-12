// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "SkillListWidget.generated.h"

class USkillData;
class UListView;
class UButton;
class USkillSystemComponent;

USTRUCT(BlueprintType)
struct FSkillDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName SkillName;

	UPROPERTY(EditAnywhere)
	UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere)
	FName SkillDesc;
};

UCLASS()
class SWORDOFVENGEANCE_API USkillListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	USkillListWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	UListView* SkillListWidget;

	UPROPERTY(meta = (BindWidget))
	UButton* SkillExitButton;

	UDataTable* SkillDataTable;

	UPROPERTY()
	USkillData* SkillData;

	USkillSystemComponent* SkillComponent;
public:

	FORCEINLINE void SetSkillComponent(USkillSystemComponent* NewSkillComponent) { SkillComponent = NewSkillComponent; }

	UFUNCTION()
	void SkillExitButtonClicked();
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListWidget.h"
#include "Widget/SkillListViewWidget.h"
#include "Components/ListView.h"
#include "DataAsset/SkillData.h"
#include "Components/ListView.h"

USkillListWidget::USkillListWidget(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer)
{
	FString DataTablePath = TEXT("Script/Engine.DataTable'/Game/Widget/DT_SkillDataTable.DT_SkillDataTable'");

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SkillDataTable(*DataTablePath);

	if (DT_SkillDataTable.Succeeded())
	{
		SkillDataTable = DT_SkillDataTable.Object;
	}
}

void USkillListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SkillDataTable == nullptr)
	{
		return;
	}

	TArray<FName> Names = SkillDataTable->GetRowNames();

	for (FName Name : Names)
	{
		FSkillDataTable* SkillDataTAble = SkillDataTable->FindRow<FSkillDataTable>(Name, "");
		if (SkillDataTAble)
		{
			SkillData = NewObject<USkillData>(this, USkillData::StaticClass());
			if (SkillData)
			{
				UTexture2D* SkillIcon = SkillDataTAble->SkillIcon;
				FName SkillDesc = SkillDataTAble->SkillDesc;

				SkillData->Init(SkillIcon, SkillDesc);

				SkillListWidget->AddItem(SkillData);
			}
		}
	}
}

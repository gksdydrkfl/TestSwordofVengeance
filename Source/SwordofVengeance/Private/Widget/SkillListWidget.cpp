// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillListWidget.h"
#include "Widget/SkillListViewWidget.h"
#include "Components/ListView.h"
#include "DataAsset/SkillData.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Kismet/GameplayStatics.h"
#include "SkillSystem/SkillSystemComponent.h"
#include "DataAsset/SkillData.h"

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

	int32 Count = 0;

	USkillData* TempData = nullptr;

	for (FName Name : Names)
	{
		FSkillDataTable* SkillDataTAble = SkillDataTable->FindRow<FSkillDataTable>(Name, "");
		if (SkillDataTAble)
		{
			SkillData = NewObject<USkillData>(this, USkillData::StaticClass());
			if (SkillData)
			{
				//구조체 묶어서 사용하면 될듯
				UTexture2D* SkillIcon = SkillDataTAble->SkillIcon;
				FName SkillDesc = SkillDataTAble->SkillDesc;
				int32 SlotIndex = Count;
				FName SkillName = SkillDataTAble->SkillName;
				bool bActive = SkillDataTAble->bActive;
				bool bCombo = SkillDataTAble->bCombo;
				SkillData->Init(SkillIcon, SkillDesc, SlotIndex, SkillName, bActive, bCombo);

				SkillListWidget->AddItem(SkillData);
				if (bCombo)
				{
					if (TempData == nullptr)
					{
						TempData = SkillData;
						TempData->List.AddUnique(TempData);
					}
					else
					{
						TempData->List.AddUnique(SkillData);
					}
				}
			}
		}
	}

	if (SkillExitButton)
	{
		SkillExitButton->OnClicked.AddDynamic(this, &USkillListWidget::SkillExitButtonClicked);
	}
}

void USkillListWidget::SkillExitButtonClicked()
{
	Debug::Log("ButtonClicked");
	RemoveFromParent();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		if (SkillComponent)
		{
			SkillComponent->SetShowSkillWidget(false);
		}
	}
}

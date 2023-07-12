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
				int32 SlotIndex = Count;
				FName SkillName = SkillDataTAble->SkillName;

				SkillData->Init(SkillIcon, SkillDesc, SlotIndex, SkillName);

				SkillListWidget->AddItem(SkillData);
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

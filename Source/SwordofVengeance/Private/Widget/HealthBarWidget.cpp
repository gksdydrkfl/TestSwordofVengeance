// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Character/Slay.h"
#include "Kismet/GameplayStatics.h"
#include "Character/AttributeComponent.h"
void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//HealthBar->PercentDelegate.BindUFunction(this, "UpdateHealth");
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Character)
	{
		ASlay* Slay = Cast<ASlay>(Character);

		Slay->GetAttribute()->HealthDelegate.AddUObject(this, &UHealthBarWidget::UpdateHealth);
	}

}
void UHealthBarWidget::UpdateHealth(float NewHealth)
{
	if (HealthBar == nullptr)
	{
		return;
	}

	const float Health = NewHealth /= 100.f;

	HealthBar->SetPercent(Health);
}


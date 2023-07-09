// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlayPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widget/GamePlayWidget.h"

ASlayPlayerController::ASlayPlayerController()
{

}

void ASlayPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GamePlayWidgetClass)
	{
		UGamePlayWidget* GamePlayWidget = CreateWidget<UGamePlayWidget>(this, GamePlayWidgetClass);
		if (GamePlayWidget)
		{
			GamePlayWidget->AddToViewport();
		}
	}
}

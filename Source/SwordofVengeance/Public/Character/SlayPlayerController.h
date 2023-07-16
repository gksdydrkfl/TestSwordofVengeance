// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlayPlayerController.generated.h"

/**
 * 
 */

class UGamePlayWidget;

UCLASS()
class SWORDOFVENGEANCE_API ASlayPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ASlayPlayerController();

protected:

	virtual void BeginPlay() override;


private:

	UPROPERTY(EditAnywhere, Category = "Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UGamePlayWidget> GamePlayWidgetClass;

	UPROPERTY()
	UGamePlayWidget* GamePlayWidget;

public:

	FORCEINLINE UGamePlayWidget* GetGamePlayWidget() const { return GamePlayWidget; };
};

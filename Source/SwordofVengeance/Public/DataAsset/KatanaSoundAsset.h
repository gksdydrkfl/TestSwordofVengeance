// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KatanaSoundAsset.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFVENGEANCE_API UKatanaSoundAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	USoundBase* DrawSwordSound;
};

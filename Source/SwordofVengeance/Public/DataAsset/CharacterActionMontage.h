// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterActionMontage.generated.h"


UCLASS()
class UCharacterActionMontage : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Katana")
	UAnimMontage* KatanaEquipMontage;

	UPROPERTY(EditAnywhere, Category = "Katana")
	UAnimMontage* KatanaUnEquipMontage;

	UPROPERTY(EditAnywhere, Category = "Katana")
	UAnimMontage* KatanaAttackMontage;

	UPROPERTY(EditAnywhere, Category = "Katana")
	UAnimMontage* KatanaGuardMontage;

	UPROPERTY(EditAnywhere, Category = "Rolling")
	UAnimMontage* RollingMontage;

	UPROPERTY(EditAnywhere, Category = "Dash")
	UAnimMontage* DashMontage;

public:
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputActions.generated.h"

class UInputAction;

UCLASS()
class UInputActions : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere)
	UInputAction* BattleModeAction;

	UPROPERTY(EditAnywhere)
	UInputAction* EquipWeaponAction;

	UPROPERTY(EditAnywhere)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere)
	UInputAction* TargetLookOnAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RollingAction;

	UPROPERTY(EditAnywhere)
	UInputAction* GuardAction;

	UPROPERTY(EditAnywhere)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere)
	UInputAction* Skill_01;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSystem/Skill/KatanaSkill.h"
#include "KatanaBaseAttack.generated.h"

class ASlay;
class UMotionWarpingComponent;
UCLASS()
class SWORDOFVENGEANCE_API UKatanaBaseAttack : public UKatanaSkill
{
	GENERATED_BODY()
	
public:

	UKatanaBaseAttack();

private:

	UPROPERTY()
	UMotionWarpingComponent* MotionWarpingComp;

	float MotionWarpingTargectDistance = 0.f;

public:

	virtual void StartSkill() override;
};

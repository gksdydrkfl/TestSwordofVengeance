// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSystem/Skill/Skill.h"
#include "KatanaBaseAttack.generated.h"

class ASlay;
class UMotionWarpingComponent;
UCLASS()
class SWORDOFVENGEANCE_API UKatanaBaseAttack : public USkill
{
	GENERATED_BODY()
	
public:

	UKatanaBaseAttack();

private:

	UMotionWarpingComponent* MotionWarpingComp;

	int32 KatanaCombo = 0;

	float MotionWarpingTargectDistance = 0.f;


public:

	virtual void StartSkill() override;

	bool CanAttackingState();

	void ResetComboAttack();

};

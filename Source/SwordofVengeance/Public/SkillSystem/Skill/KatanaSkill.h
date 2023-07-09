// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSystem/Skill/Skill.h"
#include "KatanaSkill.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFVENGEANCE_API UKatanaSkill : public USkill
{
	GENERATED_BODY()
	
public:

	UKatanaSkill();

protected:

	int32 KatanaCombo = 0;


protected:

	virtual bool CanAttackingState();

public:
	virtual void ResetComboAttack();
};

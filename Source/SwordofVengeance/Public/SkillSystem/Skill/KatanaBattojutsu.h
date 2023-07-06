// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSystem/Skill/Skill.h"
#include "KatanaBattojutsu.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFVENGEANCE_API UKatanaBattojutsu : public USkill
{
	GENERATED_BODY()
public:               

	UKatanaBattojutsu();

public:

	virtual void StartSkill() override;
};

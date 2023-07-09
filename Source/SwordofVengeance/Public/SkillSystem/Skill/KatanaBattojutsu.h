// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillSystem/Skill/KatanaSkill.h"
#include "KatanaBattojutsu.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFVENGEANCE_API UKatanaBattojutsu : public UKatanaSkill
{
	GENERATED_BODY()
public:               

	UKatanaBattojutsu();

public:

	virtual void StartSkill() override;
};

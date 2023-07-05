// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/Skill.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Slay.h"
USkill::USkill()
{
}

void USkill::Init(ASlay* Character)
{
	if (Character)
	{
		Slay = Character;
	}
}

void USkill::StartSkill()
{
}
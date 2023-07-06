// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/KatanaBattojutsu.h"
#include "Character/Animation/SlayAnimInstance.h"
#include "Character/Slay.h"
UKatanaBattojutsu::UKatanaBattojutsu()
{
	SkillType = ESkillType::EST_KatanaBattojutsu;

}

void UKatanaBattojutsu::StartSkill()
{

	USlayAnimInstance* SlayAnimInstance = Cast<USlayAnimInstance>(Slay->GetMesh()->GetAnimInstance());

	if (SlayAnimInstance)
	{
		FName SectionName = "Battojutsu";

		SlayAnimInstance->PlayAttackMontage(SectionName, 0.5f);
	}
}

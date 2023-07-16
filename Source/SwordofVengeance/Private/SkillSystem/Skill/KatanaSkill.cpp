// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/KatanaSkill.h"
#include "Character/Slay.h"
#include "Character/SlayPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/GamePlayWidget.h"
#include "Widget/SkillBarWidget.h"
UKatanaSkill::UKatanaSkill()
{
	SkillWeapon = ESkillWeapon::ESW_Katana;
}

bool UKatanaSkill::CanAttackingState()
{
	if (Slay->GetActionState() == EActionState::EAS_Evasion)
	{
		return false;
	}

	if (Slay->GetActionState() == EActionState::EAS_Attacking)
	{
		return false;
	}

	if (Slay->GetCharacterState() == ECharacterState::ECS_UnEquipped)
	{
		Slay->EquippedWeapon();

		return false;
	}

	if (Slay->GetCanAttack() == false)
	{
		return false;
	}

	//if (MotionWarpingComp == nullptr)
	//{
	//	return false;
	//}

	if (Slay->GetActionState() == EActionState::EAS_EquippingWeapon)
	{
		return false;
	}

	return true;
}

void UKatanaSkill::ResetComboAttack()
{
	if (Slay == nullptr)
	{
		return;
	}
	KatanaCombo = 0;
	Slay->SetCanAttack(true);
	Slay->SetActionState(EActionState::EAS_Unoccupied);

	if (Slay->GetSlayController())
	{
		if (Slay->GetSlayController()->GetGamePlayWidget())
		{
			if (Slay->GetSlayController()->GetGamePlayWidget()->GetSkillBarWidget())
			{
				Slay->GetSlayController()->GetGamePlayWidget()->GetSkillBarWidget()->UpdateSkillBar(ESkillType::EST_KatanaBaseAttack);
			}
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/KatanaBaseAttack.h"
#include "Character/Slay.h"
#include "MotionWarpingComponent.h"
#include "Character/Animation/SlayAnimInstance.h"

UKatanaBaseAttack::UKatanaBaseAttack()
{
	SkillType = ESkillType::EST_KatanaBaseAttack;

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp"));

}

void UKatanaBaseAttack::StartSkill()
{
	if (Slay == nullptr)
	{
		return;
	}

	bool bCanAttackingState = CanAttackingState();
	if (bCanAttackingState == false)
	{
		return;
	}

	MotionWarpingComp->RemoveWarpTarget(FName("TargetWarp"));

	Slay->SetCanAttack(false);

	if (KatanaCombo >= 3)
	{
		KatanaCombo = 0;
	}


	USlayAnimInstance* SlayAnimInstance = Cast<USlayAnimInstance>(Slay->GetMesh()->GetAnimInstance());

	if (SlayAnimInstance)
	{
		FName SectionName = FName();
		switch (KatanaCombo)
		{
		case 0:
			SectionName = FName("Combo1");
			MotionWarpingTargectDistance = 35.f;
			break;
		case 1:
			SectionName = FName("Combo2");
			MotionWarpingTargectDistance = 35.f;
			break;
		case 2:
			SectionName = FName("Combo3");
			MotionWarpingTargectDistance = 100.f;
			break;
		}
		KatanaCombo++;
		Slay->SetMotionWarpingTargectDistance(MotionWarpingTargectDistance);
		SlayAnimInstance->PlayAttackMontage(SectionName);
	}

	Slay->SetCombatMode();
}
bool UKatanaBaseAttack::CanAttackingState()
{
	if (Slay->GetActionState() == EActionState::EAS_Evasion)
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

	if (MotionWarpingComp == nullptr)
	{
		return false;
	}

	if (Slay->GetActionState() == EActionState::EAS_EquippingWeapon)
	{
		return false;
	}

	return true;
}

void UKatanaBaseAttack::ResetComboAttack()
{
	if (Slay == nullptr)
	{
		return;
	}
	KatanaCombo = 0;
	Slay->SetCanAttack(true);
	Slay->SetActionState(EActionState::EAS_Unoccupied);
}
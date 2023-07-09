// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/KatanaBattojutsu.h"
#include "Character/Animation/SlayAnimInstance.h"
#include "Character/Slay.h"
#include "Item/Equipment/Weapon/Katana.h"
UKatanaBattojutsu::UKatanaBattojutsu()
{
	SkillType = ESkillType::EST_KatanaBattojutsu;

}

void UKatanaBattojutsu::StartSkill()
{
	bool bCanAttack = CanAttackingState();


	if (bCanAttack)
	{
		Slay->SetCanAttack(false);

		USlayAnimInstance* SlayAnimInstance = Cast<USlayAnimInstance>(Slay->GetMesh()->GetAnimInstance());

		if (SlayAnimInstance)
		{
			FName SectionName = "Battojutsu";

			SlayAnimInstance->PlayAttackMontage(SectionName, 1.f);
		}

		if (Slay)
		{
			AKatana* Katana = Cast<AKatana>(Slay->GetCurrentWeapon());
			if (Katana)
			{
				Katana->SetWeaponSound(EWeaponSound::EWS_Battojutsu);
			}

		}
	}
}

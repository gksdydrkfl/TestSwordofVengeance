// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/Skill/KatanaBaseAttack.h"
#include "Character/Slay.h"
#include "MotionWarpingComponent.h"
#include "Character/Animation/SlayAnimInstance.h"
#include "Item/Equipment/Weapon/Katana.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Widget/GamePlayWidget.h"
#include "Widget/SkillBarWidget.h"
#include "Character/SlayPlayerController.h"


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

	ASlayPlayerController* SlayController = Slay->GetSlayController();

	if (SlayController == nullptr)
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

	if (GetKatanaCombo() >= 3)
	{
		SetKatanaCombo(0);
	}


	USlayAnimInstance* SlayAnimInstance = Cast<USlayAnimInstance>(Slay->GetMesh()->GetAnimInstance());
	EWeaponSound WeaponSound = EWeaponSound();

	if (SlayAnimInstance)
	{
		FName SectionName = FName();
		switch (GetKatanaCombo())
		{
		case 0:
			SectionName = FName("Combo1");
			MotionWarpingTargectDistance = 35.f;
			WeaponSound = EWeaponSound::EWS_SwordSwing1;
			break;
		case 1:
			SectionName = FName("Combo2");
			MotionWarpingTargectDistance = 35.f;
			WeaponSound = EWeaponSound::EWS_SwordSwing1;
			break;
		case 2:
			SectionName = FName("Combo3");
			MotionWarpingTargectDistance = 100.f;
			WeaponSound = EWeaponSound::EWS_SwordSwing2;
			break;
		}
		SetKatanaCombo(GetKatanaCombo() + 1);


		Slay->SetMotionWarpingTargectDistance(MotionWarpingTargectDistance);

		SlayAnimInstance->PlayAttackMontage(SectionName);
	}

	AKatana* Katana = Cast<AKatana>(Slay->GetCurrentWeapon());
	if (Katana)
	{
		Katana->SetWeaponSound(WeaponSound);
	}

	SlayController->GetGamePlayWidget()->GetSkillBarWidget()->UpdateSkillBar(ESkillType::EST_KatanaBaseAttack, GetKatanaCombo());

	Slay->SetCombatMode();
}

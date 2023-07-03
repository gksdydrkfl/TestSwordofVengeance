// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyComboEnd.h"
#include "Character/Slay.h"
#include "SkillSystem/SkillSystemComponent.h"
#include "SkillSystem/Skill/KatanaBaseAttack.h"
void UAnimNotifyComboEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		USkillSystemComponent* SkillSystem = Slay->GetSkillSystem();
		if (SkillSystem)
		{
			USkill** Skill = SkillSystem->GetSkills().Find(ESkillType::EST_KatanaBaseAttack);
			if (Skill)
			{
				UKatanaBaseAttack* KatanaBaseAttack = Cast<UKatanaBaseAttack>(*Skill);
				if (KatanaBaseAttack)
				{
					KatanaBaseAttack->ResetComboAttack();
				}
			}
		}
	}
}

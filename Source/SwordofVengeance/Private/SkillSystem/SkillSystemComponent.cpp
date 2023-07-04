// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSystem/SkillSystemComponent.h"
#include "SkillSystem/Skill/Skill.h"
#include "SkillSystem/Skill/KatanaBaseAttack.h"
#include "SwordofVengeance/DebugMacro.h"
// Sets default values for this component's properties
USkillSystemComponent::USkillSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USkillSystemComponent::Init(ASlay* Slay)
{
	UKatanaBaseAttack* KatanaBaseAttack = NewObject<UKatanaBaseAttack>(UKatanaBaseAttack::StaticClass());
	if (KatanaBaseAttack)
	{
		KatanaBaseAttack->Init(Slay);

		Skills.Add(ESkillType::EST_KatanaBaseAttack, KatanaBaseAttack);
	}
}

void USkillSystemComponent::StartSkill(const ESkillType& SkillType)
{
	NewSkill = nullptr;
	NewSkill = GetSkill(SkillType);

	if (NewSkill)
	{
		switch (SkillType)
		{
		case ESkillType::EST_KatanaBaseAttack:
			UKatanaBaseAttack* KatanaBaseAttack = Cast<UKatanaBaseAttack>(NewSkill);
			if (KatanaBaseAttack)
			{
				KatanaBaseAttack->StartSkill();
			}
			break;
		}
	}
}

USkill* USkillSystemComponent::GetSkill(const ESkillType& SkillType)
{
	if (Skills.Contains(SkillType))
	{
		USkill** Skill = Skills.Find(SkillType);

		if (*Skill)
		{
			return (*Skill);
		}

	}
	return nullptr;
}



// Called every frame
//void USkillSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillType.h"
#include "Skill.generated.h"

class ASlay;



UCLASS(BlueprintType, Blueprintable)
class SWORDOFVENGEANCE_API USkill : public UObject
{
	GENERATED_BODY()
	
public:

	USkill();

protected:

	UPROPERTY(VisibleAnywhere)
	ASlay* Slay;

	ESkillType SkillType;

	ESkillWeapon SkillWeapon;
public:

	FORCEINLINE ESkillType GetSkillType() const { return SkillType; }

	void Init(ASlay* Character);

	virtual void StartSkill();

	void UpdateSkillWidget();
};

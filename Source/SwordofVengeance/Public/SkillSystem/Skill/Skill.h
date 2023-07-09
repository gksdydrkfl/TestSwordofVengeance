// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Skill.generated.h"

class ASlay;

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	EST_KatanaBaseAttack	UMETA(DisplayName = "KatanaBaseAttack"),
	EST_KatanaBattojutsu	UMETA(DisplayName = "KatanaBattojutsu"),
};

UENUM(BlueprintType)
enum class ESkillWeapon : uint8
{
	ESW_Katana	UMETA(DisplayName = "Katana"),
};

UCLASS(BlueprintType, Blueprintable)
class SWORDOFVENGEANCE_API USkill : public UObject
{
	GENERATED_BODY()
	
public:

	USkill();

protected:

	ASlay* Slay;

	ESkillType SkillType;

	ESkillWeapon SkillWeapon;
public:

	FORCEINLINE ESkillType GetSkillType() const { return SkillType; }

	void Init(ASlay* Character);

	virtual void StartSkill();
};

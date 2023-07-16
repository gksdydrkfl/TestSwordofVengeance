#pragma once

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
#pragma once
UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_None			UMETA(DisPlayName = "None"),
	ECS_UnEquipped		UMETA(DisplayName = "UnEquipped"),
	ECS_Equipped		UMETA(DisplayName = "Equipped")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_None			UMETA(DisPlayName = "None"),
	EAS_Unoccupied		UMETA(DisplayName = "Unoccupied"),
	EAS_EquippingWeapon UMETA(DisplayName = "EquippingWeapon"),
	EAS_Attacking		UMETA(DisplayName = "Attacking"),
	EAS_Evasion			UMETA(DisplayName = "Evasion")
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	EBS_Idle			UMETA(DisPlayName = "Idle"),
	EBS_BattleMode1		UMETA(DisPlayName = "BattleMode1"),
	EBS_BattleMode2		UMETA(DisPlayName = "BattleMode2")
};
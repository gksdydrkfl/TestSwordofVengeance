// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterType.h"
#include "SlayAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMontageState : uint8
{
	EMS_Equip		 UMETA(DisplayName = "Equip"),
	EMS_UnEquip		 UMETA(DisplayName = "UnEquip")
};
UENUM(BlueprintType)
enum class EDirectionState : uint8
{
	EDS_Forward			UMETA(DisplayName = "Forward"),
	EDS_Backward		UMETA(DisplayName = "Backward"),
	EDS_Left			UMETA(DisplayName = "Left"),
	EDS_Right			UMETA(DisplayName = "Right"),
	EDS_Forward_Left	UMETA(DisplayName = "Forward_Left"),
	EDS_Forward_Right	UMETA(DisplayName = "Forward_Right"),
	EDS_Backward_Left	UMETA(DisplayName = "Backward_Left"),
	EDS_Backward_Right	UMETA(DisplayName = "Backward_Right")
};

class ASlay;
class UCharacterActionMontage;

UCLASS()
class SWORDOFVENGEANCE_API USlayAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USlayAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//TODO
	//virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = true))
	ASlay* Slay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DataAsset", meta = (AllowPrivateAccess = true))
	UCharacterActionMontage* CharacterActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
	EActionState ActionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = true))
	EDirectionState DirectionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
	bool bLockOn;

public:

	void PlayEquipMontage(EMontageState MontageState);
	void PlayAttackMontage(const FName& SectionName, float PlayRate = 1.f);
	void PlayRollingMontage(const bool& bRockOn);
	void PlayGuardMontage();

	void FindDirection();
};

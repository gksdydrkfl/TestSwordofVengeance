// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterType.h"
#include "InputActionValue.h"
#include "TargetSystem/TargetSystemInterface.h"
#include "Slay.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputActions;
class UInputMappingContext;
class AWeapon;
class USlayAnimInstance;
class UMotionWarpingComponent;
class UTargetSystemComponent;
class USkillSystemComponent;

UCLASS()
class SWORDOFVENGEANCE_API ASlay : public ACharacter, public ITargetSystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlay();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = true))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputActions* InputActions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeapon> KatanaSheathClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeapon> KatanaClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	AWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
	EActionState ActionState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
	ECharacterState CharacterState;

	int32 KatanaCombo;

	bool bCanAttack;

	USlayAnimInstance* SlayAnimInstance;

	UMotionWarpingComponent* MotionWarpingComp;

	float MotionWarpingTargectDistance;

	UPROPERTY(VisibleAnywhere)
	UTargetSystemComponent* TargetSystem;

	FTimerHandle CombatTimerHandle;

	float CombatStateTime;

	UPROPERTY(EditAnywhere, Category = "Animation Layer", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> UnarmedAnimLayer;

	UPROPERTY(EditAnywhere, Category = "Animation Layer", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> CurrentAnimLayer;

	bool bBattleMode;

	FVector LastInputDirection;

	FVector RollingDirection;

	UPROPERTY(VisibleAnywhere, Category = "Skill System", meta = (AllowPrivateAccess = true))
	USkillSystemComponent* SkillSystem;
protected:

	void Move(const FInputActionValue& Vaslue);
	void Look(const FInputActionValue& Value);
	void EquipWeapon(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void TargetLookOn(const FInputActionValue& Value);
	void Evasion(const FInputActionValue& Value);
	void Guard(const FInputActionValue& Value);

public:

	
	FORCEINLINE bool GetBattleMode() const { return bBattleMode; };
	FORCEINLINE bool GetCanAttack() const { return bCanAttack; };
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; };
	FORCEINLINE AWeapon* GetCurrentWeapon() const { return CurrentWeapon; };
	FORCEINLINE FVector GetLastInputDirection() const { return LastInputDirection; };
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTargetSystemComponent* GetTargetSystem() const { return TargetSystem; };
	FORCEINLINE USkillSystemComponent* GetSkillSystem() const { return SkillSystem; };

	FORCEINLINE void SetCanAttack(const bool& Value) { bCanAttack = Value; };
	FORCEINLINE void SetActionState(const EActionState& NewState) { ActionState = NewState; };
	FORCEINLINE void SetCharacterState(const ECharacterState& NewState) { CharacterState = NewState; };
	

public:

	void AttachWeaponToSocket(const FName& SocketName);
	void UpdateMotionWarping();
	void SetCombatMode();
	void SetNonCombatMode();
	bool CanAttackingState(const FInputActionValue& Value);
	void SetLinkAnimClassLayers(const TSubclassOf<UAnimInstance>& InClass);
	TSubclassOf<UAnimInstance> GetLinkAnimClassLayers() const;
	void EquippedWeapon();


	virtual bool IsTargetable() override;
};

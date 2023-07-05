// Fill out your copyright notice in the Description page of Project Settings.

//Character
#include "Character/Animation/SlayAnimInstance.h"
#include "DataAsset/CharacterActionMontage.h"
#include "Character/Slay.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TargetSystem/TargetSystemComponent.h"

USlayAnimInstance::USlayAnimInstance() :
	Speed(0.f),
	CharacterState(ECharacterState::ECS_None)
{
	///Script/SwordofVengeance.DataAssetCharacterMontage'/Game/Characters/Animations/DA_Montages.DA_Montages'
}

void USlayAnimInstance::NativeInitializeAnimation()
{
	//static ConstructorHelpers::FObjectFinder<UDataAssetCharacterMontage> CharacterMontage(TEXT("Script/SwordofVengeance.DataAssetCharacterMontage'/Game/Characters/Animations/DA_Montages.DA_Montages'");
	//if (CharacterMontage.Succeeded())
	//{
	//	DataAssetCharacterMontage = CharacterMontage.Object;
	//}
}

void USlayAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Slay == nullptr)
	{
		Slay = Cast<ASlay>(TryGetPawnOwner());
	}

	if (Slay == nullptr)
	{
		return;
	}

	FVector Velocity = Slay->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	CharacterState = Slay->GetCharacterState();
	ActionState = Slay->GetActionState();
	bLockOn = Slay->GetTargetSystem()->GetRockOn();
	FindDirection();
}

void USlayAnimInstance::PlayEquipMontage(EMontageState MontageState)
{
	if (CharacterActionMontage)
	{
		UAnimMontage* Montage = nullptr;

		switch (MontageState)
		{
		case EMontageState::EMS_Equip:
			Montage = CharacterActionMontage->KatanaEquipMontage;
			break;
		case EMontageState::EMS_UnEquip:
			Montage = CharacterActionMontage->KatanaUnEquipMontage;
			break;
		}

		if (Montage)
		{
			Montage_Play(Montage, 1.1f);
		}
	}
}

void USlayAnimInstance::PlayAttackMontage(const FName& SectionName)
{
	if (CharacterActionMontage)
	{
		if (CharacterActionMontage->KatanaAttackMontage)
		{
			Montage_Play(CharacterActionMontage->KatanaAttackMontage);
			Montage_JumpToSection(SectionName, CharacterActionMontage->KatanaAttackMontage);
		}
	}
}

void USlayAnimInstance::PlayRollingMontage(const bool& bRockOn)
{
	if (CharacterActionMontage == nullptr)
	{
		return;
	}

	FName SectionName = FName();

	UAnimMontage* EvasionMontage = nullptr;

	if (bRockOn == false)
	{
		EvasionMontage = CharacterActionMontage->DashMontage;
		SectionName = FName("Forward");
	}
	else
	{
		switch (DirectionState)
		{
		case EDirectionState::EDS_Forward:
			SectionName = FName("Forward");
			break;
		case EDirectionState::EDS_Backward:
			SectionName = FName("Backward");
			break;
		case EDirectionState::EDS_Left:
			SectionName = FName("Left");
			break;
		case EDirectionState::EDS_Right:
			SectionName = FName("Right");
			break;
		default:
			SectionName = FName();
			break;
		}
		EvasionMontage = CharacterActionMontage->RollingMontage;

	}

	if (EvasionMontage)
	{
		Montage_Play(EvasionMontage);
		Montage_JumpToSection(SectionName, EvasionMontage);
	}

}

void USlayAnimInstance::PlayGuardMontage()
{
	if (CharacterActionMontage)
	{
		UAnimMontage* KatanaGuardMontage = CharacterActionMontage->KatanaGuardMontage;

		if (KatanaGuardMontage)
		{
			Montage_Play(KatanaGuardMontage, 1.25f);
		}
	}
}

void USlayAnimInstance::FindDirection()
{
	if (Slay == nullptr)
	{
		return;
	}

	FVector Acceleration = Slay->GetCharacterMovement()->GetCurrentAcceleration();

	if (Acceleration.Size() <= 0.f)
	{
		Acceleration = Slay->GetActorForwardVector();
	}

	const FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Acceleration);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (Controller == nullptr)
	{
		return;
	}

	const FRotator ControllerRotation = Controller->GetControlRotation();

	const FRotator YawRotation = UKismetMathLibrary::NormalizedDeltaRotator(Rotation, ControllerRotation);

	const float Angle = YawRotation.Yaw;

	//bool Value = UKismetMathLibrary::InRange_FloatFloat(Angle, -70.f, 70.f);
	//if (Value)
	//{
	//	DirectionState = EDirectionState::EDS_Forward;
	//}
	//else
	//{
	//	Value = UKismetMathLibrary::InRange_FloatFloat(Angle, 70.f, 110.f);
	//	if (Value)
	//	{
	//		DirectionState = EDirectionState::EDS_Right;
	//	}
	//	else
	//	{
	//		Value = UKismetMathLibrary::InRange_FloatFloat(Angle, -110, -70.f);
	//		if (Value)
	//		{
	//			DirectionState = EDirectionState::EDS_Left;
	//		}
	//		else
	//		{
	//			DirectionState = EDirectionState::EDS_Backward;
	//		}
	//	}
	//}


	if (Angle < 44.f && Angle >= -44.f)
	{
		DirectionState = EDirectionState::EDS_Forward;
	}
	else if (Angle > 44.1f && Angle <= 45.9f)
	{
		DirectionState = EDirectionState::EDS_Forward_Right;
	}
	else if (Angle > 46.f && Angle <= 134.f)
	{
		DirectionState = EDirectionState::EDS_Right;
	}
	else if (Angle > 134.1f && Angle <= 135.9f)
	{
		DirectionState = EDirectionState::EDS_Backward_Right;
	}
	else if (Angle < -44.1f && Angle >= -45.9f)
	{
		DirectionState = EDirectionState::EDS_Forward_Left;
	}
	else if (Angle < -134.1 && Angle >= -135.9f)
	{
		DirectionState = EDirectionState::EDS_Backward_Left;
	}
	else if (Angle < -44.f && Angle >= -134.f)
	{
		DirectionState = EDirectionState::EDS_Left;
	}
	else
	{
		DirectionState = EDirectionState::EDS_Backward;
	}
}


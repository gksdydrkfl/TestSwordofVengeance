// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyEquip.h"
#include "Character/Slay.h"
#include "Item/Equipment/Weapon/Weapon.h"
void UAnimNotifyEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->AttachWeaponToSocket(FName("RightHandWeaponSocket"));

		Slay->SetActionState(EActionState::EAS_Unoccupied);

		Slay->SetCombatMode();

		Slay->GetCurrentWeapon()->PlaySound(EWeaponSound::EWS_DrawSword);
	}
}

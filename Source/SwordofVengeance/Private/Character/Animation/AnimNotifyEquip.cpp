// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyEquip.h"
#include "Character/Slay.h"
#include "Item/Equipment/Weapon/Katana.h"
void UAnimNotifyEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->AttachWeaponToSocket(FName("RightHandWeaponSocket"));

		Slay->SetActionState(EActionState::EAS_Unoccupied);

		Slay->SetCombatMode();

		FName ItemName = Slay->GetCurrentWeapon()->GetItemName();

		if (ItemName == FName("Katana"))
		{
			AKatana* Katana = Cast<AKatana>(Slay->GetCurrentWeapon());
			if (Katana)
			{
				Katana->PlaySound();
			}
		}
	}
}

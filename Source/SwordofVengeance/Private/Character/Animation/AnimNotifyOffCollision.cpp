// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyOffCollision.h"
#include "Character/Slay.h"
#include "Item/Equipment/Weapon/Weapon.h"
#include "SwordofVengeance/DebugMacro.h"

void UAnimNotifyOffCollision::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->GetCurrentWeapon()->DisabledBoxCollision(ECollisionEnabled::NoCollision);
	}
}

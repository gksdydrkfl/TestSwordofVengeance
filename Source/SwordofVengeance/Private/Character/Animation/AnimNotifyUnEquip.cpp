// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyUnEquip.h"
#include "Character/Slay.h"

void UAnimNotifyUnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->AttachWeaponToSocket(FName("PutSwordSocket"));
	}
}

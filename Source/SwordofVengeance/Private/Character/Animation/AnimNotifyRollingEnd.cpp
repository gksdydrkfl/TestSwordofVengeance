// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyRollingEnd.h"
#include "Character/Slay.h"

void UAnimNotifyRollingEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->ResetComboAttack();
	}
}
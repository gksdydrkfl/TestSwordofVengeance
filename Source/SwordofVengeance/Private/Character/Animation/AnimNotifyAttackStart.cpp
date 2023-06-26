// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/AnimNotifyAttackStart.h"
#include "Character/Slay.h"

void UAnimNotifyAttackStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ASlay* Slay = Cast<ASlay>(MeshComp->GetOwner());

	if (Slay)
	{
		Slay->UpdateMotionWarping();

		Slay->SetActionState(EActionState::EAS_Attacking);
	}
}

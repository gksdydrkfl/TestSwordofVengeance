// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotifyAttackStart.generated.h"

/**
 * 
 */
UCLASS()
class SWORDOFVENGEANCE_API UAnimNotifyAttackStart : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};

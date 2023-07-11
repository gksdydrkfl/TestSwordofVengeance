// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillData.generated.h"

class UTexture2D;

UCLASS(Blueprintable)
class SWORDOFVENGEANCE_API USkillData : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere)
	FName SkillDesc;

	
	int32 SlotIndex;
public:

	void Init(UTexture2D* NewTexture, FName NewSkillDesc, int32 NewSlotIndex);

	FORCEINLINE UTexture2D* GetTexture() const { return SkillIcon; }
	FORCEINLINE FName GetSkillDesc() const { return SkillDesc; }

};

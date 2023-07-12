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

	FName SkillName;
public:

	void Init(UTexture2D* NewTexture, const FName& NewSkillDesc, const int32& NewSlotIndex, const FName& NewSkillName);

	FORCEINLINE UTexture2D* GetTexture() const { return SkillIcon; }
	FORCEINLINE FName GetSkillDesc() const { return SkillDesc; }
	FORCEINLINE FName GetSkillName() const { return SkillName; }
	FORCEINLINE void SetSkillIndex(const int32& NewIndex) { SlotIndex = NewIndex; }

};

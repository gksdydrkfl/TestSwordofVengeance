// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SkillData.h"

void USkillData::Init(UTexture2D* NewTexture, FName NewSkillDesc, int32 NewSlotIndex)
{
	if (NewTexture)
	{
		SkillIcon = NewTexture;
	}
	SkillDesc = NewSkillDesc;

	SlotIndex = NewSlotIndex;
}


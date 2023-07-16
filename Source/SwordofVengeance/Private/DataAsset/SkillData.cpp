// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SkillData.h"

void USkillData::Init(UTexture2D* NewTexture, const FName& NewSkillDesc, const int32& NewSlotIndex, const FName& NewSkillName, const bool& bNewActive, const bool& NewbCombo)
{
	if (NewTexture)
	{
		SkillIcon = NewTexture;
	}
	SkillDesc = NewSkillDesc;

	SlotIndex = NewSlotIndex;

	SkillName = NewSkillName;

	bActive = bNewActive;

	bCombo = NewbCombo;
}


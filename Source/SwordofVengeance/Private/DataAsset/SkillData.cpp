// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/SkillData.h"

void USkillData::Init(UTexture2D* NewTexture, FName NewSkillDesc)
{
	if (NewTexture)
	{
		SkillIcon = NewTexture;
	}
	SkillDesc = NewSkillDesc;
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillActionNodeBase.h"
#include "SpawnObject/Child/Skill/Data/SkillDataBase.h"

FSkillActionNodeBase::FSkillActionNodeBase(const FSkillActionDataBase* Data)
{
	SkillData = Data;
}

FSkillActionNodeBase::~FSkillActionNodeBase()
{
}

float FSkillActionNodeBase::GetRate()
{
	return SkillData->Rate;
}

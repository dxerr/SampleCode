// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillActionNodeBase.h"
#include "SpawnObject/Child/Skill/Data/SkillDataBase.h"

FSkillActionNodeBase::FSkillActionNodeBase(const FSkillActionDataBase& Data)
{
	Rate = Data.Rate;
}

FSkillActionNodeBase::~FSkillActionNodeBase()
{
}

float FSkillActionNodeBase::GetRate()
{
	return Rate;
}

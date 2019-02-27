// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillDataContainer.h"

const FSkill* USkillDataContainer::FindData(int ID)
{
	return GetSkillData().FindByPredicate([=](const FSkill& el)
	{
		return el.ID == ID;
	});
}
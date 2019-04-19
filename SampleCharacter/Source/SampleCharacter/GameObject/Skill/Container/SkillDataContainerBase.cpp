// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillDataContainerBase.h"

const FSkillDataBase* USkillDataContainerBase::FindData(int ID)
{
	return GetSkillData().FindByPredicate([=](const FSkillDataBase& el)
	{
		return el.ID == ID;
	});
}
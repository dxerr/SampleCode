// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillBase.h"
#include "Container/SkillDataContainerBase.h"

void FSkillBase::Initialize(FBaseObject* owner)
{
	Owner = owner;
}

void FSkillBase::LoadData(const TCHAR * Path)
{
	SkillFactory = LoadObject<USkillDataContainerBase>(NULL, Path, NULL, LOAD_None, NULL);
	if (!SkillFactory)
	{
		UE_LOG(LogTemp, Error, TEXT("��ų ������ �ε忡 �����Ͽ����ϴ�."));
	}
}

const FSkillDataBase* FSkillBase::GetSkillData(int ID)
{
	return SkillFactory->GetSkillData().FindByPredicate([=](const FSkillDataBase& el)
	{
		return el.ID == ID;
	});
}

void FSkillBase::UseSKill(int ID)
{
	CurrentSkillData = GetSkillData(ID);
}
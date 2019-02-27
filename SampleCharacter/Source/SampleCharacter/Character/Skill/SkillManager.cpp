// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillManager.h"
#include "Global/GlobalDefine.h"
#include "Character/MyCharacter.h"

FSkillManager::FSkillManager()
{
}

FSkillManager::~FSkillManager()
{
}

void FSkillManager::Initialize(AMyCharacter* Character)
{
	Owner = Character;
}

void FSkillManager::LoadData(const TCHAR * Path)
{
	SkillFactory = LoadObject<USkillDataContainer>(NULL, Path, NULL, LOAD_None, NULL);
	if (!SkillFactory)
	{
		UE_LOG(GameLog, Error, TEXT("스킬 데이터 로드에 실패하였습니다."));
	}
}

const FSkill* FSkillManager::GetSkillData(int ID)
{
	return SkillFactory->GetSkillData().FindByPredicate([=](const FSkill& el)
	{
		return el.ID == ID;
	});
}

void FSkillManager::UseSKill(int ID)
{
	CurrentSkillData = GetSkillData(ID);
	//UpperFsm->ChangeState<FStateAttack>();
}
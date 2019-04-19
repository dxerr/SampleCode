// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SkillBase.h"

void FGameObjectPlayer::Initialize()
{

}

void FGameObjectPlayer::DeInitialize()
{
	if (UpperFsm)
	{
		delete UpperFsm;
	}

	if (Skill)
	{
		delete Skill;
	}
}

FFSMManager* FGameObjectPlayer::GetUpperFSM()
{
	return UpperFsm;
}

FSkillBase* FGameObjectPlayer::GetSkill()
{
	return Skill;
}

void FGameObjectPlayer::Update(float delta)
{
	FGameObjectDynamic::Update(delta);
	if (UpperFsm) { UpperFsm->Update(delta); }
	if (Skill) { Skill->Update(delta); }
}
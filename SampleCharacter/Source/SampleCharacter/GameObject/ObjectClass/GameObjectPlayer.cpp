// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SkillBase.h"

void UGameObjectPlayer::Initialize()
{
}

void UGameObjectPlayer::DeInitialize()
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

AActor* UGameObjectPlayer::GetActor()			{ return NULL; }
ACharacter* UGameObjectPlayer::GetCharacter()	{ return NULL; }
FFSMManager* UGameObjectPlayer::GetUpperFSM()	{ return UpperFsm; }
FSkillBase* UGameObjectPlayer::GetSkill()		{ return Skill; }

void UGameObjectPlayer::Update(float delta)
{
	Super::Update(delta);

	if (UpperFsm) { UpperFsm->Update(this, delta); }
	if (Skill) { Skill->Update(delta); }
}
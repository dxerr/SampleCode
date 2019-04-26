// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SkillBase.h"

AActor*		UGameObjectPlayer::GetActor()		{ return NULL; }
ACharacter* UGameObjectPlayer::GetCharacter()	{ return NULL; }
FFSMManager* UGameObjectPlayer::GetUpperFSM()	{ return UpperFsm; }
FSkillBase* UGameObjectPlayer::GetSkill()		{ return Skill; }

void UGameObjectPlayer::Initialize()
{
	Super::Initialize();

	SET_OBJECTYTPE(ObjectType, EGameObjectType::Player);
}

void UGameObjectPlayer::DeInitialize()
{
	Super::DeInitialize();

	if (UpperFsm)	{ delete UpperFsm; }
	if (Skill)		{ delete Skill; }
}

void UGameObjectPlayer::Update(float Delta)
{
	Super::Update(Delta);

	if (UpperFsm)	{ UpperFsm->Update(this, Delta); }
	if (Skill)		{ Skill->Update(Delta); }
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SkillBase.h"

EGameObjectType UGameObjectPlayer::GetObjectType() const    { return EGameObjectType::Player; }
AActor*		    UGameObjectPlayer::GetActor() const		    { return NULL; }
ACharacter*     UGameObjectPlayer::GetCharacter() const     { return NULL; }
FFSMManager*    UGameObjectPlayer::GetUpperFSM() const	    { return UpperFsm; }
FSkillBase*     UGameObjectPlayer::GetSkill() const		    { return Skill; }

void UGameObjectPlayer::Initialize()
{
	Super::Initialize();

	SET_OBJECTYTPE(ObjectType, UGameObjectPlayer::GetObjectType());
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
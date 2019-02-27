// Fill out your copyright notice in the Description page of Project Settings.

#include "StateBase.h"
#include "StateParams/StateParamBase.h"
#include "Character/MyCharacter.h"
#include "Character/Component/MyAnimInstance.h"
#include "Character/Skill/SkillManager.h"

FStateBase::FStateBase()
{
}

FStateBase::~FStateBase()
{
}


/*
* IdleState
*/
int FStateIdle::GetStateID()
{
	return (int)ECharacterStateBase::Idle;
}

FString FStateIdle::Name()
{
	return TEXT("IdleState");
}

void FStateIdle::Enter(AMyCharacter* Owner)
{

}

void FStateIdle::Update(AMyCharacter* Owner)
{

}

void FStateIdle::Exit(AMyCharacter* Owner)
{

}

/*
* MoveState
*/
int FStateWalk::GetStateID()
{
	return (int)ECharacterStateBase::Walk;
}

FString FStateWalk::Name()
{
	return TEXT("WalkState");
}

void FStateWalk::Enter(AMyCharacter* Owner)
{

}

void FStateWalk::Update(AMyCharacter* Owner)
{

}

void FStateWalk::Exit(AMyCharacter* Owner)
{

}


/*
*AttackState
*/
int FStateAttack::GetStateID()
{
	return (int)ECharacterStateUpperBase::Attack;
}

FString FStateAttack::Name()
{
	return TEXT("AttackState");
}

void FStateAttack::Enter(AMyCharacter* Owner)
{
	FSkillManager* skillMgr = Owner->GetSKillManager();
	if (skillMgr->CurrentSkillData)
	{
		UMyAnimInstance* anim = Owner->GetAnimInstance();
		anim->PlayUpperAni(skillMgr->CurrentSkillData->ResAni);
	}
}

void FStateAttack::Update(AMyCharacter* Owner)
{

}

void FStateAttack::Exit(AMyCharacter* Owner)
{

}
// Fill out your copyright notice in the Description page of Project Settings.

#include "StateBase.h"
#include "StateParams/StateParamBase.h"
#include "Character/MyCharacter.h"
#include "Character/Component/MyAnimInstance.h"

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
* IdleState
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
	UMyAnimInstance* anim = Cast<UMyAnimInstance>(Owner->GetMesh()->GetAnimInstance());
	anim->PlayUpperAni(ECharacterStateUpperBase::Attack, 1);
}

void FStateAttack::Update(AMyCharacter* Owner)
{

}

void FStateAttack::Exit(AMyCharacter* Owner)
{

}
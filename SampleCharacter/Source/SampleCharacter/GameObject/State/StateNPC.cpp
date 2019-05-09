// Fill out your copyright notice in the Description page of Project Settings.

#include "StateNPC.h"
#include "FSMManager.h"

int FStateNpcSpawn::GetStateID()
{
    return (int)EStateBase::Spawn;
}

FString FStateNpcSpawn::Name()
{
    return TEXT("StateNpcSpawn");
}

void FStateNpcSpawn::OnEnter(UGameObjectNonPlayer* Owner)
{
    FStateSingleNpc::OnEnter(Owner);

    Owner->GetBaseFSM()->ChangeDelayState<FStateNpcIdle>(1.5f);
}


int FStateNpcIdle::GetStateID()
{
	return (int)EStateBase::Idle;
}

FString FStateNpcIdle::Name()
{
	return TEXT("StateNpcIdle");
}

void FStateNpcIdle::OnEnter(UGameObjectNonPlayer* Owner)
{
	FStateSingleNpc::OnEnter(Owner);
}

int FStateNpcWalk::GetStateID()
{
    return (int)EStateBase::ForwardWalk;
}

FString FStateNpcWalk::Name()
{
    return TEXT("StateNpcWalk");
}

void FStateNpcWalk::OnEnter(UGameObjectNonPlayer* Owner)
{
    FStateSingleNpc::OnEnter(Owner);
}


int FStateNpcBeaten::GetStateID()
{
	return (int)EStateBase::Beaten;
}

FString FStateNpcBeaten::Name()
{
	return TEXT("StateNpcBeaten");
}

void FStateNpcBeaten::OnEnter(UGameObjectNonPlayer* Owner)
{
	FStateSingleNpc::OnEnter(Owner);
	//임의로 상태전환 시간 설정
	Owner->GetBaseFSM()->ChangeDelayPrevState(2.f);
}

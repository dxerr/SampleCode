// Fill out your copyright notice in the Description page of Project Settings.

#include "StateNPC.h"
#include "Define/StateParams.h"

int FStateNpcIdle::GetStateID()
{
	return (int)EStateBase::Idle;
}

FString FStateNpcIdle::Name()
{
	return TEXT("StateIdle");
}

void FStateNpcIdle::OnEnter(ANonePcObject* Owner)
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

void FStateNpcBeaten::OnUpdate(ANonePcObject* Owner, float Delta)
{

}
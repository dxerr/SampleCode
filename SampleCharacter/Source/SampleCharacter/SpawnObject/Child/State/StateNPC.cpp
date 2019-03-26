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
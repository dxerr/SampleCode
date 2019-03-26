// Fill out your copyright notice in the Description page of Project Settings.

#include "StateBase.h"

FStateBase::FStateBase()
{
}

FStateBase::~FStateBase()
{
}

bool FStateBase::IsChange(int StateID)
{
	//�ϴ� �⺻������ ���� ������ ������ ����
	return !IsSameState(StateID);
}

bool FStateBase::IsSameState(int StateID)
{
	return (GetStateID() == StateID);
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillLocal.h"

FSKillLocal::FSKillLocal()
{
}

FSKillLocal::~FSKillLocal()
{
}

void FSKillLocal::UseSKill(int ID)
{
	FSkillBase::UseSKill(ID);
	//UpperFsm->ChangeState<FStateAttack>();
}
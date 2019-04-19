// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectNonPlayer.h"
#include "GameObject/ActorExtend/NpcPawn.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/State/FSMManager.h"

void FGameObjectNonPlayer::Initialize()
{
	Fsm = new FFSMManager();
	Fsm->Initialize(this);
}

void FGameObjectNonPlayer::DeInitialize()
{
	delete Fsm;
}

AActor* FGameObjectNonPlayer::GetActor()
{
	return GetNpc();
}

ANpcPawn* FGameObjectNonPlayer::GetNpc()
{
	return Actor;
}

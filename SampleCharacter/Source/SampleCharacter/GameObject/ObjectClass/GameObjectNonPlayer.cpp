// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectNonPlayer.h"
#include "GameObject/ActorExtend/NpcPawn.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/State/FSMManager.h"

void UGameObjectNonPlayer::Initialize()
{
	Fsm = new FFSMManager();
	Fsm->Initialize(this);
}

void UGameObjectNonPlayer::DeInitialize()
{
	delete Fsm;
}

AActor* UGameObjectNonPlayer::GetActor()
{
	return GetNpc();
}

ANpcPawn* UGameObjectNonPlayer::GetNpc()
{
	return Actor;
}

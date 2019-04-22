// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectNonPlayer.h"
#include "GameObject/ActorExtend/NpcPawn.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateNPC.h"

void UGameObjectNonPlayer::Initialize()
{
	Super::Initialize();

	Fsm = new FFSMManager();
	Fsm->Initialize(this);
}

void UGameObjectNonPlayer::DeInitialize()
{
	Super::DeInitialize();

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

void UGameObjectNonPlayer::OnHit(UGameObjectBase* target)
{
	Super::OnHit(target);

	Fsm->ChangeState<FStateNpcBeaten>();
}

void UGameObjectNonPlayer::ActorSpawned(AActor* Spawn)
{
	Super::ActorSpawned(Spawn);

	if (Spawn)
	{
		Actor = Cast<ANpcPawn>(Spawn);
	}

	Fsm->ChangeState<FStateNpcIdle>();
}

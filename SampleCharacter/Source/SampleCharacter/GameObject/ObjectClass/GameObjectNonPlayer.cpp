// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectNonPlayer.h"
#include "GameObject/ActorExtend/NpcPawn.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateNPC.h"


EGameObjectType UGameObjectNonPlayer::GetObjectType() const   { return EGameObjectType::NonPlayer; }
AActor*		    UGameObjectNonPlayer::GetActor() const        { return GetNpc(); }
ANpcPawn*	    UGameObjectNonPlayer::GetNpc() const	      { return Actor; }

void UGameObjectNonPlayer::Initialize()
{
	Super::Initialize();

	SET_OBJECTYTPE(ObjectType, UGameObjectNonPlayer::GetObjectType());

	Fsm = new FFSMManager();
	Fsm->Initialize(this);
}

void UGameObjectNonPlayer::DeInitialize()
{
	Super::DeInitialize();

	delete Fsm;
}

void UGameObjectNonPlayer::OnHit(UGameObjectBase* Target)
{
	Super::OnHit(Target);

	Fsm->ChangeState<FStateNpcBeaten>();
}

void UGameObjectNonPlayer::ActorSpawned(AActor* Spawn)
{
	Super::ActorSpawned(Spawn);

	if (Spawn)
	{
		//액터 저장
		Actor = Cast<ANpcPawn>(Spawn);
	}

	Fsm->ChangeState<FStateNpcIdle>();
}

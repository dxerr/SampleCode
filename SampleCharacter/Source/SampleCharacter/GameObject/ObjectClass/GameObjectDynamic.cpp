// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectDynamic.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Parts/PartsBase.h"

AActor*		UGameObjectDynamic::GetActor()		{ return NULL; }
FFSMManager* UGameObjectDynamic::GetBaseFSM()	{ return Fsm; }
FPartsBase* UGameObjectDynamic::GetParts()		{ return Parts; }

void UGameObjectDynamic::Initialize()
{
	Super::Initialize();

	SET_OBJECTYTPE(ObjectType, EGameObjectType::Dynamic);
}

void UGameObjectDynamic::DeInitialize()
{
	Super::DeInitialize();

	if (Fsm)	{ delete Fsm; }
	if (Parts)	{ delete Parts; }
}

void UGameObjectDynamic::Update(float Delta)
{
	Super::Update(Delta);

	if (Fsm) { Fsm->Update(this, Delta); }
}
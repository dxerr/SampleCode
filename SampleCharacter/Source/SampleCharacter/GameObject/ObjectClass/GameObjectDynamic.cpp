// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectDynamic.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Parts/PartsBase.h"

void FGameObjectDynamic::Initialize()
{

}

void FGameObjectDynamic::DeInitialize()
{
	if (Fsm)
	{
		delete Fsm;
	}

	if (Parts)
	{
		delete Parts;
	}
}

AActor* FGameObjectDynamic::GetActor()
{
	return NULL;
}

FFSMManager* FGameObjectDynamic::GetBaseFSM()
{
	return Fsm;
}

FPartsBase* FGameObjectDynamic::GetParts()
{
	return Parts;
}

void FGameObjectDynamic::Update(float delta)
{
	FGameObjectBase::Update(delta);
	if (Fsm) { Fsm->Update(delta); }
}
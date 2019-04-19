// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectDynamic.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Parts/PartsBase.h"

void UGameObjectDynamic::Initialize()
{

}

void UGameObjectDynamic::DeInitialize()
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

AActor* UGameObjectDynamic::GetActor()
{
	return NULL;
}

FFSMManager* UGameObjectDynamic::GetBaseFSM()
{
	return Fsm;
}

FPartsBase* UGameObjectDynamic::GetParts()
{
	return Parts;
}

void UGameObjectDynamic::Update(float delta)
{
	Super::Update(delta);

	if (Fsm) { Fsm->Update(this, delta); }
}
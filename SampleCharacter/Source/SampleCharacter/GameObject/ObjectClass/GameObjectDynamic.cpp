// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectDynamic.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Parts/PartsBase.h"
#include "GameObject/Movement/MovementBase.h"

EGameObjectType UGameObjectDynamic::GetObjectType() const   { return EGameObjectType::Dynamic; }
AActor*		    UGameObjectDynamic::GetActor() const    	{ return NULL; }
FFSMManager*    UGameObjectDynamic::GetBaseFSM() const  	{ return Fsm; }
FPartsBase*     UGameObjectDynamic::GetParts() const		{ return Parts; }
FMovementBase*  UGameObjectDynamic::GetMovement() const     { return Movement; }

void UGameObjectDynamic::Initialize()
{
	Super::Initialize();

    SET_FLAG_TYPE(ObjectType, UGameObjectDynamic::GetObjectType());
}

void UGameObjectDynamic::DeInitialize()
{
	Super::DeInitialize();

	if (Fsm)	    { delete Fsm; }
	if (Parts)	    { delete Parts; }
    if (Movement)   { delete Movement; }
}

void UGameObjectDynamic::Update(float Delta)
{
	Super::Update(Delta);

	if (Fsm)        { Fsm->Update(this, Delta); }
    if (Movement)   { Movement->Update(Delta); }
}
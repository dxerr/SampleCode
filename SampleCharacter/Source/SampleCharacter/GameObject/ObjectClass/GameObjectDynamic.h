// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.h"
//#include "GameObject/State/FSMManager.h" //헤더 선언으로 error 02143발생  추후 확인해볼것

class FPartsBase;
class FFSMManager;

/**
 * 운동 능력이 있는 오브젝트 Base클래스
 * FSM, Parts, Movment 등의 기본 기능 처리
 */
class SAMPLECHARACTER_API FGameObjectDynamic : public FGameObjectBase
{
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual AActor* GetActor() override;

public:	
	virtual FPartsBase* GetParts();
	virtual FFSMManager* GetBaseFSM();

public:
	virtual void Update(float delta) override;

protected:
	FFSMManager* Fsm;
	FPartsBase* Parts;
};

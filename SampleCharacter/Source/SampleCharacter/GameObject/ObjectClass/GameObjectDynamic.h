// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.h"
//#include "GameObject/State/FSMManager.h" //헤더 선언으로 error 02143발생  추후 확인해볼것
#include "GameObjectDynamic.generated.h"

class FPartsBase;
class FMovementBase;
class FFSMManager;

/**
 * 운동 능력이 있는 오브젝트 Base클래스
 * FSM, Parts, Movment 등의 기본 기능 처리
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectDynamic : public UGameObjectBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

    virtual EGameObjectType GetObjectType() const override;
	virtual AActor* GetActor() const override;

public:	
	virtual FPartsBase* GetParts() const;
	virtual FFSMManager* GetBaseFSM() const;
    virtual FMovementBase* GetMovement() const;

public:
	virtual void Update(float Delta) override;

protected:
	FFSMManager* Fsm;
	FPartsBase* Parts;
    FMovementBase* Movement;
};

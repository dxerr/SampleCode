﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject/Movement/MovementBase.h"
#include "GameFramework/PawnMovementComponent.h"

class UGameObjectNonPlayer;

/**
 * 
 */
class SAMPLECHARACTER_API FMovementNpc : public FMovementBase
{
public:
    virtual void Initialize(UGameObjectBase* Owner);
    virtual void DeInitialize();

    virtual void Update(float Delta);

protected:
    void UpdateState(EPathFollowingStatus::Type Type);

private:
    void CallbackMove(UPathFollowingComponent* Path, FVector& Pos);
    void CallbackFinish(FAIRequestID ID, const FPathFollowingResult& Result);

protected:
    UGameObjectNonPlayer* Npc;
    UPawnMovementComponent* PawnMovement;
    
    //이동 상태 동기화 관리 변수
    //[Todo] 더좋은 방법을 찾아봐야 할듯
    EPathFollowingStatus::Type MoveStatus;

};

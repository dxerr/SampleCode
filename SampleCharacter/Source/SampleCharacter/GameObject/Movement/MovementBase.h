// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "GameObject/ObjectClass/GameObjectBase.h"

/**
 * 오브젝트 이동 처리 관련 클래스
 */
class SAMPLECHARACTER_API FMovementBase
{
public:
    virtual void Initialize(UGameObjectBase* Owner);
    virtual void DeInitialize();

    virtual void Update(float Delta);

public:
    bool IsStop();
    bool IsMove();

    void Stop();
    void Move();
    void Move(EGameObjectMoveDirType Type);
    void Move(FVector Dir);
    void Move(FVector Dir, EGameObjectMoveDirType Type);
    void Move(FVector Dir, EGameObjectMoveDirType Type, float Speed);

protected:
    virtual void OnStop();
    virtual void OnMove();

    /**
    *아직 Data 구조가 확립되어있지 않기 때문에 테스트 코드 관련 함수,변수들이 많이 존재함
    */
public:
    FORCEINLINE uint8 GetMoveType() const { return MoveType; }
    FORCEINLINE EGameObjectMoveDirType GetMoveDirType() const { return MoveDirType; }

    FORCEINLINE void SetMoveSpeed(float Val) { MoveSpeed = Val; }
    FORCEINLINE void SetDirection(const FVector& Val) { Direction = Val; }
    FORCEINLINE void SetMoveDirType(const EGameObjectMoveDirType& Val) { MoveDirType = Val; }

protected:
    void SetMoveType(EGameObjectMoveType Type);

protected:
    UGameObjectBase* Owner;
    UPathFollowingComponent* PathComponent;
    uint8 MoveType;
    EGameObjectMoveDirType MoveDirType;
    //
    FVector Direction;
    float MoveSpeed;
    //
};

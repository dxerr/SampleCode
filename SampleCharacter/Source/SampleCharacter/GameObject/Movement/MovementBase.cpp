// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementBase.h"

void FMovementBase::Initialize(UGameObjectBase* owner)
{
    Owner = owner;
}

void FMovementBase::DeInitialize()
{

}

void FMovementBase::Update(float Delta)
{

}

bool FMovementBase::IsStop()
{
    return MoveType == static_cast<uint8>(EGameObjectMoveType::None);
}

bool FMovementBase::IsMove()
{
    uint8 moveflag;
    SET_FLAG_TYPE(moveflag, EGameObjectMoveType::Run);
    SET_FLAG_TYPE(moveflag, EGameObjectMoveType::Walk);
    SET_FLAG_TYPE(moveflag, EGameObjectMoveType::Interpolation);
    return CHECK_FLAG_TYPE(MoveType, moveflag);
}

void FMovementBase::SetMoveType(EGameObjectMoveType Type)
{
    switch (Type)
    {
    case EGameObjectMoveType::None:
        MoveSpeed = 0.f;
        CLEAR_FLAG_TYPE(MoveType);
        return;                             //정지 상태 
    case EGameObjectMoveType::Walk:
        REMOVE_FLAG_TYPE(MoveType, EGameObjectMoveType::Run);
        break;
    case EGameObjectMoveType::Run:
        REMOVE_FLAG_TYPE(MoveType, EGameObjectMoveType::Walk);
        break;
    case EGameObjectMoveType::Interpolation:
        break;
    case EGameObjectMoveType::Jump:
        break;
    }

    SET_FLAG_TYPE(MoveType, Type);
}

void FMovementBase::Stop()
{
    CLEAR_FLAG_TYPE(MoveType);
    OnStop();
}

void FMovementBase::Move()
{
    OnMove();
}

void FMovementBase::Move(EGameObjectMoveDirType Type)
{
    SetMoveDirType(Type);
    Move();
}

void FMovementBase::Move(FVector Dir)
{
    SetDirection(Dir);
    Move();
}

void FMovementBase::Move(FVector Dir, EGameObjectMoveDirType Type)
{
    SetDirection(Dir);
    SetMoveDirType(Type);
    Move();
}

void FMovementBase::Move(FVector Dir, EGameObjectMoveDirType Type, float Speed)
{
    SetDirection(Dir);
    SetMoveDirType(Type);
    SetMoveSpeed(Speed);
    Move();
}

void FMovementBase::OnStop()
{

}

void FMovementBase::OnMove()
{

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementLocal.h"
#include "GameObject/ActorExtend/LocalCharacter.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateLocal.h"

void FMovementLocal::Initialize(UGameObjectBase* owner)
{
    FMovementBase::Initialize(owner);

    Local = Cast<UGameObjectLocal>(owner);
    if (Local)
    {
        CharMovement = Local->GetLocal()->GetCharacterMovement();
    }
}

void FMovementLocal::DeInitialize()
{
    FMovementBase::DeInitialize();
}

void FMovementLocal::Update(float Delta)
{
    FMovementBase::Update(Delta);

    if (false == IsStop())
    {
        //임시 이동 구현 코드들

        //내캐릭터 이동방향은 컨트롤러의 회전에 따라 동적 변경
        Direction = FRotationMatrix(Local->GetLocal()->Controller->GetControlRotation()).GetScaledAxis(MoveDirType == EGameObjectMoveDirType::SideStep ? EAxis::Y : EAxis::X);
        Local->GetLocal()->AddMovementInput(Direction, MoveSpeed);

        if (MoveDirType == EGameObjectMoveDirType::Forward && CHECK_FLAG_TYPE(MoveType, EGameObjectMoveType::Walk))
        {
            //전방 뛰기시 임시 가속 처리
            MoveSpeed += 3.f * Delta;

            float walkSpeed = FVector::DotProduct(CharMovement->Velocity, Local->GetLocal()->GetActorRotation().Vector());
            if (walkSpeed > CharMovement->MaxWalkSpeed)
            {
                SetMoveType(EGameObjectMoveType::Run);
                Local->GetBaseFSM()->ChangeState<FStateRun>();
            }
        }
    }
}

void FMovementLocal::OnStop()
{
    FMovementBase::OnStop();

    SetMoveType(EGameObjectMoveType::None);
    CharMovement->SetMovementMode(MOVE_None);

    Local->GetBaseFSM()->ChangeState<FStateIdle>();
}

void FMovementLocal::OnMove()
{
    FMovementBase::OnMove();

    SetMoveType(EGameObjectMoveType::Walk);
    CharMovement->SetMovementMode(MOVE_Walking);

    //상태 전환
    FFSMManager* fsm = Local->GetBaseFSM();
    switch (MoveDirType)
    {
    case EGameObjectMoveDirType::Forward:
        fsm->ChangeState<FStateForwardWalk>();
        break;
    case EGameObjectMoveDirType::SideStep:
        fsm->ChangeState<FStateSideWalk>();
        break;
    case EGameObjectMoveDirType::Backward:
        fsm->ChangeState<FStateBackwardWalk>();
        break;
    }
}

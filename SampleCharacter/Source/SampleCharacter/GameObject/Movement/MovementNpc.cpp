// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementNpc.h"
#include "AIModule/Classes/AIController.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/ActorExtend/NpcPawn.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateNPC.h"

void FMovementNpc::Initialize(UGameObjectBase* owner)
{
    FMovementBase::Initialize(owner);

    Npc = Cast< UGameObjectNonPlayer>(owner);
    if (Npc)
    {
        PawnMovement = Npc->GetNpc()->GetPawnMovement();

        AController* controller = Npc->GetNpc()->GetController();
        if (AAIController* Ai = Cast< AAIController>(controller))
        {
            //이동 동기화용 델리게이트 연결
            PathComponent = Ai->FindComponentByClass<UPathFollowingComponent>();
            if (PathComponent)
            {
                PathComponent->PostProcessMove.BindRaw(this, &FMovementNpc::CallbackMove);
                PathComponent->OnRequestFinished.AddRaw(this, &FMovementNpc::CallbackFinish);
            }
        }
    }
}

void FMovementNpc::DeInitialize()
{
    FMovementBase::DeInitialize();
}

void FMovementNpc::Update(float Delta)
{
    FMovementBase::Update(Delta);

    //상태 동기화
    if (PathComponent)
    {
        EPathFollowingStatus::Type status = PathComponent->GetStatus();
        if (MoveStatus != status)
        {
            MoveStatus = status;

            UpdateState(MoveStatus);
        }
    }
}

void FMovementNpc::UpdateState(EPathFollowingStatus::Type Type)
{
    //상태 전환
    FFSMManager* fsm = Npc->GetBaseFSM();
    switch (Type)
    {
    case EPathFollowingStatus::Idle:
        fsm->ChangeState<FStateNpcIdle>();
        break;
    case EPathFollowingStatus::Waiting:
        break;
    case EPathFollowingStatus::Paused:
        break;
    case EPathFollowingStatus::Moving:
        fsm->ChangeState<FStateNpcWalk>();
        break;
    default:
        break;
    }
}

//패스 컴퍼넌트 콜백 연결
void FMovementNpc::CallbackMove(UPathFollowingComponent* Path, FVector& Pos)
{
}

void FMovementNpc::CallbackFinish(FAIRequestID ID, const FPathFollowingResult& Result)
{
}

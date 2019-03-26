// Fill out your copyright notice in the Description page of Project Settings.

#include "StateLocal.h"

#include "Define/StateParams.h"

#include "FSMManager.h"
#include "SpawnObject/Child/LocalPlayerObject.h"
#include "SpawnObject/Child/Skill/SKillLocal.h"
#include "SpawnObject/Child/Component/Movement/CharacterMovementComponentLocal.h"
#include "SpawnObject/Child/Component/Animation/AnimInstanceState.h"

/// FStateIdle ///
int FStateIdle::GetStateID()
{
	return (int)EStateBase::Idle;
}

FString FStateIdle::Name()
{
	return TEXT("StateIdle");
}

void FStateIdle::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	Owner->GetCharacterMovement()->SetMovementMode(MOVE_None);
}


/// FStateForwardWalk ///
int FStateForwardWalk::GetStateID()
{
	return (int)EStateBase::ForwardWalk;
}

FString FStateForwardWalk::Name()
{
	return TEXT("StateForwardWalk");
}

void FStateForwardWalk::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 1000.f;
	Owner->MovementForce = 1.f;
}

void FStateForwardWalk::OnUpdate(ALocalPlayerObject* Owner, float Delta)
{
	Owner->MovementForce += 3.f * Delta;
	UpdateSpeed(Owner, Owner->MovementForce);
}

void FStateForwardWalk::UpdateSpeed(ALocalPlayerObject* Owner, float Speed)
{
	FVector dir = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->AddMovementInput(dir, Speed);

	auto movement = Owner->GetCharacterMovement();
	float walkSpeed = FVector::DotProduct(movement->Velocity, Owner->GetActorRotation().Vector());
	UE_LOG(LogTemp, Warning, TEXT("FStateForwardWalk Speed %f"), walkSpeed);
	if (walkSpeed > movement->MaxWalkSpeed)
	{
		Owner->GetLowwerState()->ChangeState<FStateRun>();
	}
}


/// FStateBackwardWalk ///
int FStateBackwardWalk::GetStateID()
{
	return (int)EStateBase::BackwardWalk;
}

FString FStateBackwardWalk::Name()
{
	return TEXT("StateBackwardWalk");
}

void FStateBackwardWalk::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 500.f;
	Owner->MovementForce = -0.5f;
}

void FStateBackwardWalk::OnUpdate(ALocalPlayerObject* Owner, float Delta)
{
	FVector dir = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->AddMovementInput(dir, Owner->MovementForce);
}


/// FStateSideWalk ///
int FStateSideWalk::GetStateID()
{
	return (int)EStateBase::SideWalk;
}

FString FStateSideWalk::Name()
{
	return TEXT("StateSideWalk");
}

void FStateSideWalk::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 500.f;
	//Owner->MovementForce = -0.5f;
}

void FStateSideWalk::OnUpdate(ALocalPlayerObject* Owner, float Delta)
{
	FVector dir = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Owner->AddMovementInput(dir, Owner->MovementForce);
}


/// FStateRun ///
int FStateRun::GetStateID()
{
	return (int)EStateBase::Run;
}

FString FStateRun::Name()
{
	return TEXT("StateRun");
}

bool FStateRun::IsChange(int StateID)
{
	switch (StateID)
	{
	case (int)EStateBase::ForwardWalk:
		return true;
	}
	return false;
}

void FStateRun::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 2000.f;
}

void FStateRun::OnUpdate(ALocalPlayerObject* Owner, float Delta)
{
	Owner->MovementForce += Delta;
	FVector dir = FRotationMatrix(Owner->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->AddMovementInput(dir, Owner->MovementForce);
}


/// FStateAttack ///
int FStateAttack::GetStateID()
{
	return (int)EStateUpperBase::Attack;
}

FString FStateAttack::Name()
{
	return TEXT("StateAttack");
}

void FStateAttack::OnEnter(ALocalPlayerObject* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	FSKillLocal* skillMgr = Owner->GetSKill();
	if (skillMgr->CurrentSkillData)
	{
		UAnimInstanceState* anim = Owner->GetAnim();
		anim->PlayUpperAni(skillMgr->CurrentSkillData->ResAni);
	}
}

void FStateAttack::OnUpdate(ALocalPlayerObject* Owner, float Delta)
{

}
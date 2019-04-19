// Fill out your copyright notice in the Description page of Project Settings.

#include "StateLocal.h"
#include "FSMManager.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/Component/Animation/AnimInstanceState.h"

#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"


/// FStateIdle ///
int FStateIdle::GetStateID()
{
	return (int)EStateBase::Idle;
}

FString FStateIdle::Name()
{
	return TEXT("StateIdle");
}

void FStateIdle::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	Owner->GetLocal()->GetCharacterMovement()->SetMovementMode(MOVE_None);
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

void FStateForwardWalk::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetLocal()->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 1000.f;
	Owner->MovementForce = 1.f;
}

void FStateForwardWalk::OnUpdate(UGameObjectLocal* Owner, float Delta)
{
	Owner->MovementForce += 3.f * Delta;
	UpdateSpeed(Owner, Owner->MovementForce);
}

void FStateForwardWalk::UpdateSpeed(UGameObjectLocal* Owner, float Speed)
{
	FVector dir = FRotationMatrix(Owner->GetLocal()->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->GetLocal()->AddMovementInput(dir, Speed);

	auto movement = Owner->GetLocal()->GetCharacterMovement();
	float walkSpeed = FVector::DotProduct(movement->Velocity, Owner->GetLocal()->GetActorRotation().Vector());
	UE_LOG(LogTemp, Warning, TEXT("FStateForwardWalk Speed %f"), walkSpeed);
	if (walkSpeed > movement->MaxWalkSpeed)
	{
		Owner->GetBaseFSM()->ChangeState<FStateRun>();
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

void FStateBackwardWalk::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetLocal()->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 500.f;
	Owner->MovementForce = -0.5f;
}

void FStateBackwardWalk::OnUpdate(UGameObjectLocal* Owner, float Delta)
{
	FVector dir = FRotationMatrix(Owner->GetLocal()->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->GetLocal()->AddMovementInput(dir, Owner->MovementForce);
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

void FStateSideWalk::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetLocal()->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 500.f;
	//Owner->MovementForce = -0.5f;
}

void FStateSideWalk::OnUpdate(UGameObjectLocal* Owner, float Delta)
{
	FVector dir = FRotationMatrix(Owner->GetLocal()->Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Owner->GetLocal()->AddMovementInput(dir, Owner->MovementForce);
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

void FStateRun::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	auto movement = Owner->GetLocal()->GetCharacterMovement();
	movement->SetMovementMode(MOVE_Walking);
	movement->MaxWalkSpeed = 2000.f;
}

void FStateRun::OnUpdate(UGameObjectLocal* Owner, float Delta)
{
	Owner->MovementForce += Delta;
	FVector dir = FRotationMatrix(Owner->GetLocal()->Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	Owner->GetLocal()->AddMovementInput(dir, Owner->MovementForce);
}

///FStateUpperIdle///
int FStateUpperIdle::GetStateID()
{
	return (int)EStateUpperBase::Idle;
}

FString FStateUpperIdle::Name()
{
	return TEXT("StateUpperIdle");
}

void FStateUpperIdle::OnEnter(UGameObjectLocal* Owner)
{
	//상체 애니 재생 정지
	FSkillBase* skillMgr = Owner->GetSkill();
	if (skillMgr->CurrentSkillData)
	{
		UAnimInstanceState* anim = Owner->GetLocal()->GetAnim();
		anim->StopUpperAni(skillMgr->CurrentSkillData->GetAni());
	}
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

void FStateAttack::OnEnter(UGameObjectLocal* Owner)
{
	FStateSingleLocal::OnEnter(Owner);

	FSkillBase* skillMgr = Owner->GetSkill();
	if (skillMgr->CurrentSkillData)
	{
		UAnimInstanceState* anim = Owner->GetLocal()->GetAnim();
		anim->PlayUpperAni(skillMgr->CurrentSkillData->GetAni());
		skillMgr->OnSKillNode();
	}
}

void FStateAttack::OnUpdate(UGameObjectLocal* Owner, float Delta)
{
	FSkillBase* skillMgr = Owner->GetSkill();
	skillMgr->RunSkillNode(Delta);
}
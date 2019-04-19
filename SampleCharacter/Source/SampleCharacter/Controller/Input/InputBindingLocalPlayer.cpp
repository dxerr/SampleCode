// Fill out your copyright notice in the Description page of Project Settings.

#include "InputBindingLocalPlayer.h"
#include "GameObject/ActorExtend/LocalCharacter.h"
#include "GameObject/Parts/PartsLocal.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateLocal.h"

//[Todo]타겟 클래스 설정 방식에 좀더 좋은 구조를 생각해볼것
void UInputBindingLocalPlayer::Initialize()
{
	//error
}

void UInputBindingLocalPlayer::Initialize(FGameObjectLocal* target)
{
	Target = target;
}

void UInputBindingLocalPlayer::SetBinding(UInputComponent* input)
{
	Super::SetBinding(input);

	input->BindAction<FOnAttachParts>("AttachPartsH", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::HEAD);
	input->BindAction<FOnAttachParts>("AttachPartsB", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::BODY);
	input->BindAction<FOnAttachParts>("AttachPartsG", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::GLOVE);
	input->BindAction<FOnAttachParts>("AttachPartsL", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::LEG);
	input->BindAction<FOnAttachParts>("AttachPartsHair", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::HAIR);
	input->BindAction<FOnAttachParts>("AttachPartsFace", IE_Released, this, &UInputBindingLocalPlayer::OnAttachParts, EPartsType::FACE);

	//key
	input->BindAction<FOnAttack1>("Attack1", IE_Released, this, &UInputBindingLocalPlayer::OnAttack1, 1);
	input->BindAction<FOnAttack1>("Attack2", IE_Released, this, &UInputBindingLocalPlayer::OnAttack1, 2);
	input->BindAction<FOnAttack1>("Attack3", IE_Released, this, &UInputBindingLocalPlayer::OnAttack1, 3);

	//Movement
	input->BindAction("MoveForward", IE_Pressed, this, &UInputBindingLocalPlayer::OnMoveForward);
	input->BindAction("MoveBackward", IE_Pressed, this, &UInputBindingLocalPlayer::OnMoveBackward);
	input->BindAction("MoveLeft", IE_Pressed, this, &UInputBindingLocalPlayer::OnMoveLeft);
	input->BindAction("MoveRight", IE_Pressed, this, &UInputBindingLocalPlayer::OnMoveRight);
	input->BindAction("MoveStop", IE_Released, this, &UInputBindingLocalPlayer::OnMoveStop);

	input->BindAxis("MoveRotate", this, &UInputBindingLocalPlayer::OnMoveRotateYaw);
	input->BindAxis("Turn", this, &UInputBindingLocalPlayer::OnMoveRotateYaw);
	input->BindAxis("LookUp", this, &UInputBindingLocalPlayer::OnMoveRotatePitch);
}

void UInputBindingLocalPlayer::OnAttachParts(EPartsType Type)
{
	if (FPartsBase* parts = Target->GetParts())
	{
		parts->IsEquip(Type) ? parts->Detach(Type) : parts->Attach(Type);
		Target->GetActor()->GetActorRotation();
	}
}

void UInputBindingLocalPlayer::OnAttack1(int32 slot)
{
	if (FSkillBase* skill = Target->GetSkill())
	{
		skill->UseSKill(slot);
	}
}

void UInputBindingLocalPlayer::OnMoveStop()
{
	if (FFSMManager* fsm = Target->GetBaseFSM())
	{
		fsm->ChangeState<FStateIdle>();
	}
}

void UInputBindingLocalPlayer::OnMoveForward()
{
	if (FFSMManager* fsm = Target->GetBaseFSM())
	{
		fsm->ChangeState<FStateForwardWalk>();
	}
}

void UInputBindingLocalPlayer::OnMoveBackward()
{
	if (FFSMManager* fsm = Target->GetBaseFSM())
	{
		fsm->ChangeState<FStateBackwardWalk>();
	}
}

void UInputBindingLocalPlayer::OnMoveLeft()
{
	Target->MovementForce = -0.5f; //Movement 구현으로 추후 대체되야함

	if (FFSMManager* fsm = Target->GetBaseFSM())
	{
		fsm->ChangeState<FStateSideWalk>();
	}
}

void UInputBindingLocalPlayer::OnMoveRight()
{
	Target->MovementForce = 0.5f; //Movement 구현으로 추후 대체되야함

	if (FFSMManager* fsm = Target->GetBaseFSM())
	{
		fsm->ChangeState<FStateSideWalk>();
	}
}

void UInputBindingLocalPlayer::OnMoveRotate(float Value)
{
	FVector dir = FRotationMatrix(Target->GetLocal()->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Target->GetLocal()->AddMovementInput(dir, Value);
}

void UInputBindingLocalPlayer::OnMoveRotateYaw(float Value)
{
	Target->GetLocal()->AddControllerYawInput(Value);
}

void UInputBindingLocalPlayer::OnMoveRotatePitch(float Value)
{
	Target->GetLocal()->AddControllerPitchInput(Value);
}

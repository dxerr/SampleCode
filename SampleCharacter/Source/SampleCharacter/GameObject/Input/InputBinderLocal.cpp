// Fill out your copyright notice in the Description page of Project Settings.

#include "InputBinderLocal.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "GameObject/ObjectClass/GameObjectBase.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"
#include "GameObject/Parts/PartsLocal.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/State/StateLocal.h"


// Add default functionality here for any IInputBinderLocal functions that are not pure virtual.

void UInputBinderLocal::InitBind(FGameObjectLocal* Owner, UInputComponent* InputComponent)
{
	Local = Owner;

	InputComponent->BindAction<FOnAttachParts>("AttachPartsH", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::HEAD);
	InputComponent->BindAction<FOnAttachParts>("AttachPartsB", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::BODY);
	InputComponent->BindAction<FOnAttachParts>("AttachPartsG", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::GLOVE);
	InputComponent->BindAction<FOnAttachParts>("AttachPartsL", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::LEG);
	InputComponent->BindAction<FOnAttachParts>("AttachPartsHair", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::HAIR);
	InputComponent->BindAction<FOnAttachParts>("AttachPartsFace", IE_Released, this, &UInputBinderLocal::OnAttachParts, EPartsType::FACE);

	//key
	InputComponent->BindAction<FOnAttack1>("Attack1", IE_Released, this, &UInputBinderLocal::OnAttack1, 1);
	InputComponent->BindAction<FOnAttack1>("Attack2", IE_Released, this, &UInputBinderLocal::OnAttack1, 2);
	InputComponent->BindAction<FOnAttack1>("Attack3", IE_Released, this, &UInputBinderLocal::OnAttack1, 3);

	//Movement
	InputComponent->BindAction("MoveForward", IE_Pressed, this, &UInputBinderLocal::OnMoveForward);
	InputComponent->BindAction("MoveBackward", IE_Pressed, this, &UInputBinderLocal::OnMoveBackward);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &UInputBinderLocal::OnMoveLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &UInputBinderLocal::OnMoveRight);
	InputComponent->BindAction("MoveStop", IE_Released, this, &UInputBinderLocal::OnMoveStop);

	InputComponent->BindAxis("MoveRotate", this, &UInputBinderLocal::OnMoveRotateYaw);
	InputComponent->BindAxis("Turn", this, &UInputBinderLocal::OnMoveRotateYaw);
	InputComponent->BindAxis("LookUp", this, &UInputBinderLocal::OnMoveRotatePitch);
}

void UInputBinderLocal::OnAttachParts(EPartsType Type)
{
	if (FPartsBase* parts = Local->GetParts())
	{
		parts->IsEquip(Type) ? parts->Detach(Type) : parts->Attach(Type);
		Local->GetActor()->GetActorRotation();
	}
}

void UInputBinderLocal::OnAttack1(int32 slot)
{
	if (FSkillBase* skill = Local->GetSkill())
	{
		skill->UseSKill(slot);
	}
}

void UInputBinderLocal::OnMoveStop()
{
	if (FFSMManager* fsm = Local->GetBaseFSM())
	{
		fsm->ChangeState<FStateIdle>();
	}
}

void UInputBinderLocal::OnMoveForward()
{
	if (FFSMManager* fsm = Local->GetBaseFSM())
	{
		fsm->ChangeState<FStateForwardWalk>();
	}
}

void UInputBinderLocal::OnMoveBackward()
{
	if (FFSMManager* fsm = Local->GetBaseFSM())
	{
		fsm->ChangeState<FStateBackwardWalk>();
	}
}

void UInputBinderLocal::OnMoveLeft()
{
	Local->MovementForce = -0.5f; //Movement 구현으로 추후 대체되야함

	if (FFSMManager* fsm = Local->GetBaseFSM())
	{
		fsm->ChangeState<FStateSideWalk>();
	}
}

void UInputBinderLocal::OnMoveRight()
{
	Local->MovementForce = 0.5f; //Movement 구현으로 추후 대체되야함

	if (FFSMManager* fsm = Local->GetBaseFSM())
	{
		fsm->ChangeState<FStateSideWalk>();
	}
}

void UInputBinderLocal::OnMoveRotate(float Value)
{
	FVector dir = FRotationMatrix(Local->GetLocal()->GetControlRotation()).GetScaledAxis(EAxis::Y);
	Local->GetLocal()->AddMovementInput(dir, Value);
}

void UInputBinderLocal::OnMoveRotateYaw(float Value)
{
	Local->GetLocal()->AddControllerYawInput(Value);
}

void UInputBinderLocal::OnMoveRotatePitch(float Value)
{
	Local->GetLocal()->AddControllerPitchInput(Value);
}

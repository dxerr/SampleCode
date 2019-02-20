// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "SampleCharacter/Character/MyCharacter.h"
#include "SampleCharacter/Character/State/FSMManager.h"
#include "SampleCharacter/Character/State/StateBase.h"

UMyAnimInstance::UMyAnimInstance()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CurrUpperAni.IsEnd())
	{
		CurrUpperAni.Clear();
		//ChangeUpperState(CurrUpperAni.ReturnState, 0);
	}
}

void UMyAnimInstance::ChangeState(int State)
{
	if (State >= (int)ECharacterStateUpperBase::None)
	{
		UpperStateType = static_cast<ECharacterStateUpperBase>(State);
	}
	else
	{
		BaseStateType = static_cast<ECharacterStateBase>(State);
	}
	
}

bool UMyAnimInstance::IsState(ECharacterStateBase State)
{
	return BaseStateType == State;
}

bool UMyAnimInstance::IsUpperState(ECharacterStateUpperBase State)
{
	return UpperStateType == State;
}

bool UMyAnimInstance::IsUpperBlend()
{
	return BaseStateType != ECharacterStateBase::Idle;
}

void UMyAnimInstance::PlayUpperAni(ECharacterStateUpperBase ChangeState, int Id)
{
	auto find = UpperParams.Params.FindByPredicate([=](const FStateUpperParam& el)
	{
		return el.EStateType == ChangeState;
	});

	if (nullptr != find)
	{
		auto findele = find->OriElements.FindByPredicate([=](const FStateUpperElement& el)
		{
			return el.ID == Id;
		});

		if (nullptr != findele)
		{
			CurrUpperAni.ReturnState = ECharacterStateUpperBase::None;

			PlayUpperAnimation(findele->ResAni);
		}
	}

	/*
	if (UpperFsmMgr)
	{
		GAME_WARN("ChangeUpperState : %s", *UpperFsmMgr->CurrentState()->Name());
	}*/
}

void UMyAnimInstance::PlayUpperAnimation(UAnimMontage* Animation)
{
	CurrUpperAni.Ani		= Animation;
	CurrUpperAni.Timer		= FApp::GetCurrentTime();
	CurrUpperAni.Duration	= Animation->GetPlayLength();

	Montage_Play(CurrUpperAni.Ani);
}
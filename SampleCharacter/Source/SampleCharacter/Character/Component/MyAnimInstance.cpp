// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance()
{
	//�⺻ �Ҽ� ��� ����
	if (SocialActions.IsValidIndex(0))
	{
		currentSocialAction = SocialActions[0].Ani;
	}

	CurrStateType = ECharacterStateBase::Idle;
	CurrUpperStateType = ECharacterStateUpperBase::None;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CurrUpperAni.IsEnd())
	{
		CurrUpperAni.Clear();
		ChangeUpperState(CurrUpperAni.ReturnState, 0);
	}
}

ECharacterStateBase UMyAnimInstance::GetCurrentStateType()
{
	return CurrStateType;
}

UAnimMontage* UMyAnimInstance::CurrBlendAnimation() const
{
	return CurrUpperAni.Ani;
}

bool UMyAnimInstance::IsState(ECharacterStateBase State)
{
	return CurrStateType == State;
}

bool UMyAnimInstance::IsUpperState(ECharacterStateUpperBase State)
{
	return CurrUpperStateType == State;
}

void UMyAnimInstance::OnSocialPlay_Implementation(int Index)
{
	//�ش� �ε����� �Ҽ� �׼� �ִ� ����
	if (SocialActions.IsValidIndex(Index))
	{
		currentSocialAction = SocialActions[Index].Ani;
	}
}

void UMyAnimInstance::ChangeState_Implementation(ECharacterStateBase ChangeState)
{
	CurrStateType = ChangeState;

	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECharacterStateBase"), true);
	if (enumPtr)
	{
		GAME_WARN("ChangeState : %s", *enumPtr->GetEnumName((int32)ChangeState));
	}
}

bool UMyAnimInstance::IsUpperBlend()
{
	return CurrStateType == ECharacterStateBase::Walk;
}

void UMyAnimInstance::ChangeUpperState_Implementation(ECharacterStateUpperBase ChangeState, int Id)
{
	CurrUpperStateType = ChangeState;
	auto find = UpperParams.Params.FindByPredicate([=](const FStateUpperParam& el)
	{
		return el.EStateType == CurrUpperStateType;
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

	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECharacterStateUpperBase"), true);
	if (enumPtr)
	{
		GAME_WARN("ChangeUpperState : %s", *enumPtr->GetEnumName((int32)ChangeState));
	}
}

void UMyAnimInstance::PlayUpperAnimation(UAnimMontage* Animation)
{
	CurrUpperAni.Ani		= Animation;
	CurrUpperAni.Timer		= FApp::GetCurrentTime();
	CurrUpperAni.Duration	= Animation->GetPlayLength();

	Montage_Play(CurrUpperAni.Ani);
}

UAnimMontage* UMyAnimInstance::GetCurrentSocialAction() const
{
	return currentSocialAction;
}
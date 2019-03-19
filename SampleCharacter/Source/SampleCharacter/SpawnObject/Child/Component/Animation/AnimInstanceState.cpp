// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstanceState.h"

bool UAnimInstanceState::IsState(EStateBase State)
{
	return BaseStateType == State;
}

bool UAnimInstanceState::IsStates(const TArray<EStateBase>& States)
{
	for (auto el : States)
	{
		if (el == BaseStateType)
		{
			return true;
		}
	}

	return false;

	/*
	return States.Contains([=](const ECharacterStateBase& el)
	{
		return BaseStateType == el;
	});*/
}

bool UAnimInstanceState::IsUpperState(EStateUpperBase State)
{
	return UpperStateType == State;
}

bool UAnimInstanceState::IsUpperBlend()
{
	return BaseStateType != EStateBase::Idle;
}

bool UAnimInstanceState::IsMoveState()
{
	return BaseStateType != EStateBase::Idle;
}

void UAnimInstanceState::ChangeState(int State)
{
	if (State >= (int)EStateUpperBase::None)
	{
		UpperStateType = static_cast<EStateUpperBase>(State);
	}
	else
	{
		BaseStateType = static_cast<EStateBase>(State);
	}

	UE_LOG(LogTemp, Warning, TEXT("UAnimInstanceLocal ChangeState Lowwer : %d  Upper : %d"), (int)BaseStateType, (int)UpperStateType);
}

void UAnimInstanceState::PlayUpperAni(UAnimMontage* Animation)
{
	Montage_Play(Animation);
}


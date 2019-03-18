// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstanceLocal.h"

bool UAnimInstanceLocal::IsState(EStateBase State)
{
	return BaseStateType == State;
}

bool UAnimInstanceLocal::IsStates(const TArray<EStateBase>& States)
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

bool UAnimInstanceLocal::IsUpperState(EStateUpperBase State)
{
	return UpperStateType == State;
}

bool UAnimInstanceLocal::IsUpperBlend()
{
	return BaseStateType != EStateBase::Idle;
}

bool UAnimInstanceLocal::IsMoveState()
{
	return BaseStateType != EStateBase::Idle;
}

void UAnimInstanceLocal::ChangeState(int State)
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

void UAnimInstanceLocal::PlayUpperAni(UAnimMontage* Animation)
{
	Montage_Play(Animation);
}
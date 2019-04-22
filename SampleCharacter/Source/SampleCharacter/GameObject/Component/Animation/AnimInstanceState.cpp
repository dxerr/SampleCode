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
	return IsMoveState();
}

bool UAnimInstanceState::IsMoveState()
{
	return BaseStateType == EStateBase::ForwardWalk ||
		BaseStateType == EStateBase::BackwardWalk ||
		BaseStateType == EStateBase::SideWalk ||
		BaseStateType == EStateBase::Run;
}

int UAnimInstanceState::GetRandomIndex()
{
	return RandomIndex;
}

void UAnimInstanceState::ChangeState(int State, int min, int max)
{
	if (State >= (int)EStateUpperBase::None)
	{
		UpperStateType = static_cast<EStateUpperBase>(State);
	}
	else
	{
		BaseStateType = static_cast<EStateBase>(State);
	}

	//·£´ý ÀÎµ¦½º »ý¼º
	if (max - min > 0)
	{
		RandomIndex = FMath::RandRange(min, max);
	}
	else
	{
		RandomIndex = 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("UAnimInstanceLocal ChangeState Lowwer : %d  Upper : %d"), (int)BaseStateType, (int)UpperStateType);
}

void UAnimInstanceState::PlayUpperAni(UAnimMontage* res)
{
	Montage_Play(res);
}

void UAnimInstanceState::StopUpperAni(UAnimMontage* res)
{
	Montage_Stop(0.2f, res);
}


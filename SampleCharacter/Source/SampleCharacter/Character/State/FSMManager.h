// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StateBase.h"

/**
 * 
 */
class SAMPLECHARACTER_API FFSMManager
{
public:
	FFSMManager();
	virtual ~FFSMManager();

	FORCEINLINE FStateBase* CurrentState() const { return Current; }
	FORCEINLINE FStateBase* PrevState() const { return Prev; }
	FORCEINLINE bool IsState(int StateID)
	{
		return (nullptr != Current && Current->GetStateID() == StateID);
	}

	void Initialize(class AMyCharacter* Character);

	template <typename T>
	void ChangeState();

private:
	//UAnimInstance 를 상속 받은 베이스
	class AMyCharacter* Owner;

	FStateBase* Current;
	FStateBase* Prev;
};

template <class T>
void FFSMManager::ChangeState()
{
	T* state = T::GetInstance();

	check(state);
	if (nullptr != Current && Current->GetStateID() != state->GetStateID())
	{
		Current->Exit(Owner);
		Prev = Current;
	}

	Current = state;
	Current->Enter(Owner);

	Owner->GetAnimInstance()->ChangeState(Current->GetStateID());
}


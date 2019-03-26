// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/GlobalDefine.h"
#include "StateBase.h"
#include "SpawnObject/Util/Owner.h"

/**
 * 
 */
class SAMPLECHARACTER_API FFSMManager
{
public:
	FORCEINLINE FStateBase* CurrentState() const { return Current; }
	FORCEINLINE FStateBase* PrevState() const { return Prev; }
	FORCEINLINE bool IsState(int StateID)
	{
		return (nullptr != Current && Current->GetStateID() == StateID);
	}

	void Initialize(FBaseObject* owner);
	void Update(float Delta);

	template <typename T>
	void ChangeState();

private:
	FBaseObject* Owner;

	FStateBase* Current;
	FStateBase* Prev;
};

template <typename T>
void FFSMManager::ChangeState()
{
	T* state = T::GetInstance();

	check(state);
	if (nullptr != Current)
	{
		//체인지 가능 여부 검사
		if (false == state->IsChange(Current->GetStateID()))
		{
			//
			//실패에 대한 델리게이트를 연결하여 호출 상황에 맞게 유동적인 대처를 유도한다.
			//
			return;
		}

		//애님 블루프린트의 FSM전환 가능 여부를 알수 있다면 여기서 검사
		//

		if (Current->GetStateID() != state->GetStateID())
		{
			//중복 상태 호출 확인
			if (Current->GetStateID() == state->GetStateID())
			{
				Current->ReEnter(Owner);
				UE_LOG(LogTemp, Warning, TEXT("%s State ReEnter"), *Current->Name());
				return;
			}

			Current->Exit(Owner);
			UE_LOG(LogTemp, Warning, TEXT("%s State Eixt!! Prev(%s) Curr(%s)"), *Current->Name(), *Current->Name(), nullptr != Prev ? *Prev->Name() : TEXT("null"));
			LOG_S(Warning);
			Prev = Current;
		}
	}

	Current = state;
	Current->Enter(Owner);
	UE_LOG(LogTemp, Warning, TEXT("%s State Enter"), *Current->Name());

	//Owner->GetAnimInstance()->ChangeState(Current->GetStateID());
}


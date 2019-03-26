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
		//ü���� ���� ���� �˻�
		if (false == state->IsChange(Current->GetStateID()))
		{
			//
			//���п� ���� ��������Ʈ�� �����Ͽ� ȣ�� ��Ȳ�� �°� �������� ��ó�� �����Ѵ�.
			//
			return;
		}

		//�ִ� �������Ʈ�� FSM��ȯ ���� ���θ� �˼� �ִٸ� ���⼭ �˻�
		//

		if (Current->GetStateID() != state->GetStateID())
		{
			//�ߺ� ���� ȣ�� Ȯ��
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


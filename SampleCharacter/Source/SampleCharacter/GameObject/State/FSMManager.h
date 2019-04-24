// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/GlobalDefine.h"
#include "StateBase.h"
#include "Define/StateParams.h"
#include "GameObject/ObjectClass/GameObjectBase.h"

/**
 * 
 */
class SAMPLECHARACTER_API FFSMManager
{
public:
	FORCEINLINE FStateBase* CurrentState() const { return Current; }
	FORCEINLINE FStateBase* PrevState() const	{ return Prev; }
	FORCEINLINE bool IsState(int StateID)
	{
		return (nullptr != Current && Current->GetStateID() == StateID);
	}

	//region
	void Initialize(UGameObjectBase* Owner);
	void DeInitialize();

	template <class Char>
	void Update(Char* Owner, float Delta);
	template <class State>
	bool ChangeState(FStateChangeFailed const& FailDelegate = nullptr);
	//FTimerManager를 통한 이벤트 처리 일정 시간후 스테이트 전환
	template <class State>
	void ChangeDelayState(float Time);
	void ChangeDelayState(FStateBase* State, float Time);
	void ChangeDelayPrevState(float Time);

private:
	bool ChangeState(FStateBase* State, FStateChangeFailed const& FailDelegate = NULL);
	void CallbakChangeState(FStateBase* State);

private:
	UGameObjectBase* Owner;
	FStateBase* Current;
	FStateBase* Prev;
};

template <class Char>
void FFSMManager::Update(Char* Owner, float Delta)
{
	if (nullptr != Current)
	{
		Current->Update(Owner, Delta);
	}
}

template <class State>
bool FFSMManager::ChangeState(FStateChangeFailed const& FailDelegate)
{
	State* state = State::GetInstance();
	return ChangeState(state, FailDelegate);
}

template <class State>
void FFSMManager::ChangeDelayState(float Time)
{
	State* state = State::GetInstance();
	ChangeDelayState(state, Time);
}
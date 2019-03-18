// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <mutex>
#include "SpawnObject/BaseObject.h"

template <typename T>
class StateSingleton
{
protected:
	StateSingleton() = default;
	//StateSingleton(const StateSingleton<T>& rhs) = delete;
	//StateSingleton<T>& operator = (const StateSingleton<T>& rhs) = delete;

private:
	static std::unique_ptr<T> _instance;
	static std::once_flag _flag1;

public:
	static T* GetInstance() {
		std::call_once(_flag1, []() {
			_instance.reset(new T);
		});

		return _instance.get();
	}
};

template <typename T> std::unique_ptr<T> StateSingleton<T>::_instance;
template <typename T> std::once_flag StateSingleton<T>::_flag1;

/**
 * 
 */
class ALocalPlayerObject;

class SAMPLECHARACTER_API FStateBase
{
public:
	FStateBase();
	virtual ~FStateBase();

	virtual int GetStateID() = 0;
	virtual FString Name() = 0;

	//체인지 가능 or 불가능 상태 정의
	virtual bool IsChange(int StateID);

	virtual void Enter(FBaseObject* Owner)	= 0;
	virtual void ReEnter(FBaseObject* Owner) = 0;
	virtual void Update(FBaseObject* Owner, float Delta) = 0;
	virtual void Exit(FBaseObject* Owner) = 0;
};

template <typename T>
class SAMPLECHARACTER_API FStateTargetBase : public FStateBase
{
public:
	virtual void Enter(FBaseObject* Owner) override
	{
		T* castOwner = static_cast<T*>(Owner->cast());
		OnEnter(castOwner);
	}
	virtual void ReEnter(FBaseObject* Owner)override
	{
		T* castOwner = static_cast<T*>(Owner->cast());
		OnReEnter(castOwner);
	}
	virtual void Update(FBaseObject* Owner, float Delta)override
	{
		T* castOwner = static_cast<T*>(Owner->cast());
		OnUpdate(castOwner, Delta);
	}
	virtual void Exit(FBaseObject* Owner)override
	{
		T* castOwner = static_cast<T*>(Owner->cast());
		OnExit(castOwner);
	}

protected:
	virtual void OnEnter(T* Owner) = 0;
	virtual void OnReEnter(T* Owner) = 0;
	virtual void OnUpdate(T* Owner, float Delta) = 0;
	virtual void OnExit(T* Owner) = 0;
};

template <typename T>
class SAMPLECHARACTER_API FStateSingleBase : public FStateBase, public StateSingleton<T>
{
public:
	FStateSingleBase() = default;
};


template <typename T>
class SAMPLECHARACTER_API FStateSingleLocal : public StateSingleton<T>, public FStateTargetBase<ALocalPlayerObject>
{
protected:
	//애님 블루프린트에 가장 최우선으로 상태를 전송해줘야한다.
	virtual void OnEnter(ALocalPlayerObject* Owner) override
	{
		UAnimInstanceLocal* anim = Owner->GetAnim();
		anim->ChangeState(GetStateID());
	}

	virtual void OnReEnter(ALocalPlayerObject* Owner) override
	{

	}
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override
	{

	}
	virtual void OnExit(ALocalPlayerObject* Owner) override
	{

	}
};
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
class SAMPLECHARACTER_API FStateBase
{
public:
	FStateBase();
	virtual ~FStateBase();

	virtual int GetStateID() = 0;
	virtual FString Name() = 0;

	//ü���� ���� or �Ұ���(Black List | White List) ���� ����
	virtual bool IsChange(int StateID);
	virtual bool IsSameState(int StateID);

	virtual void Enter(FBaseObject* Owner)	= 0;
	virtual void ReEnter(FBaseObject* Owner) = 0;
	virtual void Update(FBaseObject* Owner, float Delta) = 0;
	virtual void Exit(FBaseObject* Owner) = 0;
};

/**
* FSM�� ���� Ŭ�������� ���� ȣ��ǰ�, �̱��� ��ü�̹Ƿ� ���߻�ӿ� ���� ĳ���ú���(Owner->cast())
* ���� ���ø� �������� ����
*/
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



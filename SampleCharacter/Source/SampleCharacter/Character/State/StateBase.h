// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <mutex>

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
class AMyCharacter;

class SAMPLECHARACTER_API FStateBase
{
public:
	FStateBase();
	virtual ~FStateBase();

	virtual int GetStateID() = 0;
	virtual FString Name() = 0;

	virtual void Enter(AMyCharacter* Owner) = 0;
	//virtual void ReEnter(AMyCharacter* Owner) = 0;
	virtual void Update(AMyCharacter* Owner) = 0;
	virtual void Exit(AMyCharacter* Owner) = 0;
};

template <typename T>
class SAMPLECHARACTER_API FStateSingleBase : public FStateBase, public StateSingleton<T>
{
public:
	FStateSingleBase() = default;
};


class SAMPLECHARACTER_API FStateIdle : public FStateSingleBase<FStateIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void Enter(AMyCharacter* Owner) override;
	virtual void Update(AMyCharacter* Owner) override;
	virtual void Exit(AMyCharacter* Owner) override;
};

class SAMPLECHARACTER_API FStateWalk : public FStateSingleBase<FStateWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void Enter(AMyCharacter* Owner) override;
	virtual void Update(AMyCharacter* Owner) override;
	virtual void Exit(AMyCharacter* Owner) override;
};

class SAMPLECHARACTER_API FStateAttack : public FStateSingleBase<FStateAttack>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void Enter(AMyCharacter* Owner) override;
	virtual void Update(AMyCharacter* Owner) override;
	virtual void Exit(AMyCharacter* Owner) override;
};

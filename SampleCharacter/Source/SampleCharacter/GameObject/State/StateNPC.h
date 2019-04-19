// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GameObject/Component/Animation/AnimInstanceState.h"

/*
template <typename T>
class SAMPLECHARACTER_API FStateSingleNpc : public StateSingleton<T>, public FStateTargetBase<ANonePcObject>
{
protected:
	//애님 블루프린트에 가장 최우선으로 상태를 전송해줘야한다.
	virtual void OnEnter(ANonePcObject* Owner) override
	{
		UAnimInstanceState* anim = Owner->GetAnim();
		anim->ChangeState(GetStateID());
	}

	virtual void OnReEnter(ANonePcObject* Owner) override
	{

	}
	virtual void OnUpdate(ANonePcObject* Owner, float Delta) override
	{

	}
	virtual void OnExit(ANonePcObject* Owner) override
	{

	}
};

/**
 * 
 */
/*
class SAMPLECHARACTER_API FStateNpcIdle : public FStateSingleNpc<FStateNpcIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ANonePcObject* Owner) override;
};

class SAMPLECHARACTER_API FStateNpcBeaten : public FStateSingleNpc<FStateNpcBeaten>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ANonePcObject* Owner) override;
};
*/
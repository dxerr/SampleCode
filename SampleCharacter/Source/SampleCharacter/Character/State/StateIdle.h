// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateParams/StateParamBase.h"

namespace CharState
{
	/**
	*
	*/
	static class SAMPLECHARACTER_API FStateBase
	{
	public:
		FStateBase();
		virtual ~FStateBase();

	public:

	protected:
		virtual void ChangeState();
	};


	static class SAMPLECHARACTER_API FStateIdle : public FStateBase
	{
		virtual void ChangeState() override;
	};
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateParams.generated.h"

/**
 * 
 */
 //Lowwer State Define
UENUM()
enum class EStateBase : uint8
{
	None,
	Idle = 1,
	ForwardWalk,
	BackwardWalk,
	SideWalk,
	Run,

	BaseMax,
};

//Upper State Define
UENUM()
enum class  EStateUpperBase : uint8
{
	None = (uint8)EStateBase::BaseMax,
	Idle,
	Attack,
	BaseMax,
};

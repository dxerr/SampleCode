// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "StateParams.generated.h"

/**
 * 
 */
 //Lowwer State Define
UENUM()
enum class EStateBase : uint8
{
	None = 0,
	Spawn,
	Idle,
	ForwardWalk,
	BackwardWalk,
	SideWalk,
	Run,

	Beaten,
	Die,

	BaseMax,
};

//Upper State Define
UENUM()
enum class  EStateUpperBase : uint8
{
	None = 100,
	Idle,
	Attack,

	UpperBaseMax,
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SAMPLECHARACTER_API FBaseObject
{
public:
	FBaseObject();
	virtual ~FBaseObject() = default;

	virtual void* cast() = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/SkeletalMeshMerge.h"
#include "Data/PartsDataBase.h"

class FBaseObject;
class UActorComponent;
class UPartsDataContainerBase;

/**
 * 
 */
class SAMPLECHARACTER_API FPartsBase
{
public:
	FPartsBase();
	virtual ~FPartsBase();

	virtual void Initialize(FBaseObject* owner);
	virtual void LoadData(const TCHAR * Path);

	virtual void Attach(EPartsType Type, ...);
	virtual void Detach(EPartsType Type, ...);

	const FPartsDataBase* GetParts(EPartsType Type);		//추후 리소스 Load로 수정
	bool IsEquip(EPartsType Type);

protected:
	FBaseObject* Owner;
	
	UPartsDataContainerBase* PartsFctory;
	TArray<const FPartsDataBase*> Parts;
};
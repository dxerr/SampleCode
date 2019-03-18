// Fill out your copyright notice in the Description page of Project Settings.

#include "PartsBase.h"
#include "Container/PartsDataContainerBase.h"
#include "Data/PartsDataBase.h"

FPartsBase::FPartsBase()
{

}

FPartsBase::~FPartsBase()
{

}

void FPartsBase::Initialize(FBaseObject* Character)
{
	Owner = Character;
}

void FPartsBase::LoadData(const TCHAR * Path)
{
	PartsFctory = LoadObject<UPartsDataContainerBase>(NULL, Path, NULL, LOAD_None, NULL);
	if (!PartsFctory)
	{
		UE_LOG(LogTemp, Error, TEXT("파츠 데이터 로드에 실패하였습니다."));
	}
}

const FPartsDataBase* FPartsBase::GetParts(EPartsType Type)
{
	return PartsFctory->GetPartsData().FindByPredicate([=](const FPartsDataBase& el)
	{
		return el.Type == Type;
	});
}

bool FPartsBase::IsEquip(EPartsType Type)
{
	return Parts.ContainsByPredicate([=](const FPartsDataBase* el)
	{
		return el->Type == Type;
	});
}

void FPartsBase::Attach(EPartsType Type, ...)
{
}

void FPartsBase::Detach(EPartsType Type, ...)
{
}



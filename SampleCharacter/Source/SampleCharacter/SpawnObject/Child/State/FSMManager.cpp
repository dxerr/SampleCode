// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMManager.h"

void FFSMManager::Initialize(FBaseObject* owner)
{
	Owner = owner;
	Current = nullptr;
	Prev = nullptr;
}

void FFSMManager::Update(float Delta)
{
	if (nullptr != Current)
	{
		Current->Update(Owner, Delta);
	}
}
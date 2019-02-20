// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMManager.h"
#include "Character/MyCharacter.h"

FFSMManager::FFSMManager()
{
}

FFSMManager::~FFSMManager()
{

}

void FFSMManager::Initialize(AMyCharacter* Character)
{
	Owner = Character;
	Current = nullptr;
	Prev = nullptr;
}


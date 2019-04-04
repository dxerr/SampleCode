// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillActionNodeProjectile.h"


FSKillActionNodeProjectile::FSKillActionNodeProjectile(const FSkillActionDataBase* Data) :
	FSkillActionNodeBase(Data)
{

}

void FSKillActionNodeProjectile::Process(FBaseObject* Owner)
{

}

void FSKillActionNodeProjectile::Action(FBaseObject* Owner)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Skill!!!"));
}
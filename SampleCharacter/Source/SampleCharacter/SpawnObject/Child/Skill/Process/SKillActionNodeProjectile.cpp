// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillActionNodeProjectile.h"
#include "SpawnObject/Child/ProjectileObject.h"

#include "SampleCharacterGameModeBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"


FSKillActionNodeProjectile::FSKillActionNodeProjectile(const FSkillActionDataBase& Data) :
	FSkillActionNodeBase(Data)
{

}

void FSKillActionNodeProjectile::Process(FBaseObject* Owner)
{

}

void FSKillActionNodeProjectile::Action(FBaseObject* Owner)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Skill!!!"));
	
	if (AActor* castOwner = static_cast<AActor*>(Owner->cast()))
	{
		ASampleCharacterGameModeBase* gameMode = Cast<ASampleCharacterGameModeBase>(castOwner->GetWorld()->GetAuthGameMode());
		if (gameMode)
		{
			TWeakPtr<FObjectSpawner> spawner = gameMode->GetSpawner();
			if (spawner.IsValid())
			{
				spawner.Pin()->SpawnProjectile(castOwner);
			}
		}
	}
}
﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillActionNodeProjectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameInstanceExtend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"
#include "Controller/ObjectSpawner.h"

FSKillActionNodeProjectile::FSKillActionNodeProjectile(const FSkillActionDataBase& Data) :
	FSkillActionNodeBase(Data)
{

}

void FSKillActionNodeProjectile::Process(UGameObjectBase* Owner)
{

}

void FSKillActionNodeProjectile::Action(UGameObjectBase* Owner)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Skill!!!"));
	UGameInstanceExtend* gameInst = Cast<UGameInstanceExtend>(Owner->GetActor()->GetWorld()->GetGameInstance());
	if (gameInst)
	{
		if (UObjectSpawner* spawner = gameInst->GetSpawner())
		{
			//임시 데이터 리소스 하드코딩
			FString path = TEXT("Blueprint'/Game/Blueprints/GameObject/BP_ProjectileActor.BP_ProjectileActor'");
			if (UObject* loadObject = StaticLoadObject(UObject::StaticClass(), nullptr, *path))
			{
				FVector Pos = Owner->GetActor()->GetActorLocation() + Owner->GetActor()->GetActorForwardVector() * 100.f;

				//현재는 임시로 캐릭터 방향과 맞춤
				FRotator Rot = Owner->GetActor()->GetActorRotation();

				//블루 프린트로 캐스팅 필요 
				//이걸 하지않으면 AActor클래스 정보를 스폰시에 찾을수 없는듯 하다.
				if (UBlueprint* castBP = Cast<UBlueprint>(loadObject))
				{
					spawner->SpawnProjectile(castBP->GeneratedClass, Pos, Rot);
				}
			}
		}
	}
}
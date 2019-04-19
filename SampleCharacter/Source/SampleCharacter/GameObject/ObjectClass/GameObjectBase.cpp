// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"

FGameObjectBase::FGameObjectBase()
{
}

FGameObjectBase::~FGameObjectBase()
{
}

void FGameObjectBase::Update(float delta)
{
}

AActor* FGameObjectBase::Spawn(UClass* Instance, UWorld* World, const FVector& Position, const FRotator& dir)
{
	FActorSpawnParameters SpawnInfo;
	//스폰완료 델리게이트 연결
	//이 델리게이트는 브로드 캐스팅이다. 즉 다른 액터 스폰시에도 응답
	//World->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateRaw(this, &FGameObjectBase::ActorSpawned));
	AActor* actor = World->SpawnActor(Instance, &Position, &dir, SpawnInfo);

	ActorSpawned(actor);

	return actor;
}

void FGameObjectBase::ActorSpawned(AActor* spawn)
{
	if (spawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor Spawn Complete"), *spawn->GetName());
	}
}
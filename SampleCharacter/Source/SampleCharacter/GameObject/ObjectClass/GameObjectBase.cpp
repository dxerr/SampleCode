// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UGameObjectBase::~UGameObjectBase()
{
	UE_LOG(LogTemp, Warning, TEXT("~UGameObjectBase (%s)"), *GetName());
}

//프로퍼티
EGameObjectType UGameObjectBase::GetObjectType() const      { return EGameObjectType::Base; }
uint32          UGameObjectBase::GetObjectTypeMask() const  { return ObjectType; }
AActor*         UGameObjectBase::GetActor() const           { return NULL; }
//

void UGameObjectBase::Initialize()
{
	SET_OBJECTYTPE(ObjectType, UGameObjectBase::GetObjectType());
}

void UGameObjectBase::DeInitialize()
{
	//액터가 존재한다면 소멸
	if (AActor* actor = GetActor())
	{
		actor->GetWorld()->DestroyActor(actor);
	}
}


void UGameObjectBase::Update(float Delta)
{
}

void UGameObjectBase::OnHit(UGameObjectBase* Target)
{
}

AActor* UGameObjectBase::Spawn(UClass* Instance, UWorld* World, const FVector& Position, const FRotator& Dir)
{
	FActorSpawnParameters SpawnInfo;
	//스폰완료 델리게이트 연결
	//이 델리게이트는 브로드 캐스팅이다. 즉 다른 액터 스폰시에도 응답
	//World->AddOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateRaw(this, &UGameObjectBase::ActorSpawned));
	AActor* actor = World->SpawnActor(Instance, &Position, &Dir, SpawnInfo);
	ActorSpawned(actor);

	return actor;
}

void UGameObjectBase::ActorSpawned(AActor* Spawn)
{
	if (Spawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Actor Spawn Complete"), *Spawn->GetName());
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstanceExtend.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Core/Public/Containers/Ticker.h"
#include "Controller/PlayerControllerExpend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"

UGameInstanceExtend::UGameInstanceExtend()
{
}

void UGameInstanceExtend::Init()
{
	//Tick 델리게이트 설정
	if (TickDelegate.IsValid())
	{
		FTicker::GetCoreTicker().RemoveTicker(TickDelegate);
	}
	TickDelegate = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGameInstanceExtend::Tick));

	Spawner = NewObject<UObjectSpawner>();
	Spawner->Initialize(GetWorld());
}

void UGameInstanceExtend::Shutdown()
{
	//Spawner->DeInitialize();
	//Spawner.Reset();
}

bool UGameInstanceExtend::Tick(float delta)
{
	Spawner->Update(delta);
	return true;
}

//로컬 플레이어 스폰 담당
void UGameInstanceExtend::SpawnPlayer(TSubclassOf<ACharacter> ActorClass, const FVector& StartPos, const FVector& Offset)
{
	Spawner->SpawnPlayer(ActorClass.Get(), StartPos + Offset, FRotator(0.f, 0.f, 0.f));
}

AActor* UGameInstanceExtend::SpawnOnGround(TSubclassOf<AActor> ActorClass, const FVector& StartPos, const FVector& Offset)
{
	UGameObjectBase* obj = Spawner->SpawnNpc(ActorClass.Get(), StartPos, FRotator(0.f, 0.f, 0.f));
	return  obj->GetActor();
}

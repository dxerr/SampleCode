// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.generated.h"

class AActor;

/**
 * 모든 스폰 관련 오브젝트들의 base클래스
 * 언리얼엔진에서 제공하는 로직을 제외한 오브젝트에 대한 클라이언트 로직 처리 담당 
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize();
	virtual void DeInitialize();

public:
	//기본적인 Actor클래스 얻기
	virtual AActor* GetActor();

public:
	virtual AActor* Spawn(UClass* instance, UWorld* world, const FVector& position, const FRotator& dir);
	virtual void Update(float delta);

protected:
	//스폰 완료시 호출
	virtual void ActorSpawned(AActor* spawn);
};

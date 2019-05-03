// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "GameObjectBase.generated.h"

class AActor;

/**
 * 모든 스폰 관련 오브젝트들의 base클래스
 * 언리얼엔진에서 제공하는 로직을 제외한 오브젝트에 대한 클라이언트 로직 처리 담당 
 */
UCLASS(BlueprintType)
class SAMPLECHARACTER_API UGameObjectBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual ~UGameObjectBase();

	virtual void Initialize();
	virtual void DeInitialize();

//프로퍼티
public:
    //GameObject 타입값 얻기
    UFUNCTION(BlueprintCallable, Category = "GameObject")
    virtual EGameObjectType GetObjectType() const;
	//타입 조합값 얻기
	virtual uint32 GetObjectTypeMask() const;

	//기본적인 Actor클래스 얻기
    UFUNCTION(BlueprintCallable, Category = "GameObject")
	virtual AActor* GetActor() const;

//메서드
public:
	virtual AActor* Spawn(UClass* Instance, UWorld* World, const FVector& Position, const FRotator& Dir);
	virtual void Update(float Delta);

	//충돌 이벤트
	virtual void OnHit(UGameObjectBase* Target);

protected:
	//스폰 완료시 호출
	virtual void ActorSpawned(AActor* Spawn);

//맴버 변수
protected:
	uint8 ObjectType;
};

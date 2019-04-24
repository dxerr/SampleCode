// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "ObjectSpawner.generated.h"

class AActor;
class UPrimitiveComponent;
class UGameObjectBase;
class FObjectCollider;

/**
 * 임시 스폰 담당 클래스
 * 액터 디스폰 델리게이트 연결 이슈로 UObject형으로 처리(다른 방법이 있는지 확인)
 */
UCLASS()
class SAMPLECHARACTER_API UObjectSpawner : public UObject
{
	GENERATED_BODY()
	
public:
	void Initialize(UWorld* World);
	void DeInitialize();

	UGameObjectBase* FindObject(AActor* Actor);

	void Update(float Delta);

	//[Todo] 임시 오브젝트 스폰 처리 메서드들..
	//추후 특정 스폰 데이터형을 입력받아 처리하게 변경 필요
	UGameObjectBase* SpawnPlayer(UClass* Uclass, const FVector& Pos, const FRotator& Rot);
	UGameObjectBase* SpawnNpc(UClass* Uclass, const FVector& Pos, const FRotator& Rot);
	UGameObjectBase* SpawnProjectile(UClass* Uclass, const FVector& Pos, const FRotator& Rot);

	void DespawnObject(UGameObjectBase* Despawn);
	//

protected:
	void RemoveGameObject(UGameObjectBase* Despawn);

	UFUNCTION()
	void CallbackCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void CallbackActorDeSpawn(AActor* Despawn);

private:
	//현재 월드 정보
	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = true))
	UWorld* World;

	//액터 객체 관리
	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = true))
	TArray<UGameObjectBase*> Spawns;

	//추가/삭제 대상 관리
	TArray<UGameObjectBase*> AddSpawns;
	TArray<UGameObjectBase*> RemoveSpawns;
};

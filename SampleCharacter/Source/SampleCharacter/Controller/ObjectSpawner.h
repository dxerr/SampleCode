// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectSpawner.generated.h"

class AActor;
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
	void Initialize(UWorld* world);
	void DeInitialize();

	void Update(float delta);

	//[Todo] 임시 오브젝트 스폰 처리 메서드들..
	//추후 특정 스폰 데이터형을 입력받아 처리하게 변경 필요
	UGameObjectBase* SpawnPlayer(UClass* uclass, const FVector& pos, const FRotator& rot);
	UGameObjectBase* SpawnNpc(UClass* uclass, const FVector& pos, const FRotator& rot);
	UGameObjectBase* SpawnProjectile(UClass* uclass, const FVector& pos, const FRotator& rot);

	void DespawnObject(UGameObjectBase* despawn);
	//

protected:
	void RemoveGameObject(UGameObjectBase* despawn);

	UFUNCTION()
	void CallbackActorDeSpawn(AActor* despawn);

private:
	//액터 객체 관리
	TArray<UGameObjectBase*> Spawns;
	//임시 충돌객체 관리 클래스
	TSharedPtr<FObjectCollider> Collider;
	//현재 월드 정보
	//TSharedPtr로는 해제 타이밍을 잘잡아줘야 할듯
	//TSharedPtr<UWorld> World;
	UWorld* World;
};

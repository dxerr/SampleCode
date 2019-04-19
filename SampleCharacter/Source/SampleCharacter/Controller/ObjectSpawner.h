// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AActor;
class FGameObjectBase;
class FObjectCollider;
/**
 * 임시 스폰 담당 클래스
 */
class SAMPLECHARACTER_API FObjectSpawner
{
public:
	FObjectSpawner();

	void Initialize(UWorld* world);
	void DeInitialize();

	void Update(float delta);

	//[Todo] 임시 오브젝트 스폰 처리 메서드들..
	//추후 특정 스폰 데이터형을 입력받아 처리하게 변경 필요
	FGameObjectBase* SpawnPlayer(UClass* uclass, const FVector& pos, const FRotator& rot);
	FGameObjectBase* SpawnNpc(UClass* uclass, const FVector& pos, const FRotator& rot);
	FGameObjectBase* SpawnProjectile(UClass* uclass, const FVector& pos, const FRotator& rot);
	//

private:
	//액터 객체 관리
	TArray<FGameObjectBase*> Spawns;
	//임시 충돌객체 관리 클래스
	TSharedPtr<FObjectCollider> Collider;
	//현재 월드 정보
	//TSharedPtr로는 해제 타이밍을 잘잡아줘야 할듯
	//TSharedPtr<UWorld> World;
	UWorld* World;
};

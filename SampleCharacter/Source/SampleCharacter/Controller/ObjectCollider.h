// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

/**
 * 필요 할런지 모르겠지만 임시 충돌 객체 관리 클래스 
 * 현재는 Spawner 하위 종속으로 둔다.
 */
class SAMPLECHARACTER_API FObjectCollider
{
public:
	FObjectCollider();
	~FObjectCollider();

	void AddObject(class AActor* Target);

private:
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

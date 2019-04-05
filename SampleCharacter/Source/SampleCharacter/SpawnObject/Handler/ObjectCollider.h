// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * �ʿ� �ҷ��� �𸣰����� �ӽ� �浹 ��ü ���� Ŭ���� 
 * ����� Spawner ���� �������� �д�.
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

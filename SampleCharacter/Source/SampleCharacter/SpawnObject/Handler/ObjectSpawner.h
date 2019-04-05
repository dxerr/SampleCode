// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AActor;
class FObjectCollider;
/**
 * �ӽ� ���� ��� Ŭ����
 */
class SAMPLECHARACTER_API FObjectSpawner
{
public:
	FObjectSpawner();
	~FObjectSpawner();

	void SpawnProjectile(AActor* Owner);

private:
	TSharedPtr<FObjectCollider> Collider;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectCollider.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"

FObjectCollider::FObjectCollider()
{
}

FObjectCollider::~FObjectCollider()
{
}

void FObjectCollider::AddObject(AActor* Target)
{
	//UObject�� ��ӹ��� ���� Ŭ���� �ɹ� �Լ��� ��������Ʈ ��� Ȯ���غ���
	if (UPrimitiveComponent* collider = Target->FindComponentByClass<UPrimitiveComponent>())
	{
		//collider->OnComponentHit.AddDynamic(this, &FObjectCollider::OnCompHit);
	}
}

void FObjectCollider::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

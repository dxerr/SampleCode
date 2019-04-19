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
	//UObject를 상속받지 않은 클래스 맴버 함수의 델리게이트 등록 확인해볼것
	if (UPrimitiveComponent* collider = Target->FindComponentByClass<UPrimitiveComponent>())
	{
		//collider->OnComponentHit.AddDynamic(this, &FObjectCollider::OnCompHit);
	}
}

void FObjectCollider::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

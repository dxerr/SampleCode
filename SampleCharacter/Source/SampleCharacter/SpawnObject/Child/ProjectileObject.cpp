// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileObject.h"
#include "SpawnObject/Child/NonePcObject.h"


#include "SpawnObject/Child/State/StateNPC.h"
#include "SpawnObject/Child/State/FSMManager.h"

AProjectileObject::AProjectileObject()
{
	OnActorHit.AddDynamic(this, &AProjectileObject::OnHit);
}

void AProjectileObject::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit!! sle %s other %s"), *SelfActor->GetName(), *OtherActor->GetName());	

	//테스트용
	//이곳에 존재하면 안되는 코드이다.
	if (OtherActor)
	{
		if (ANonePcObject* npc = Cast<ANonePcObject>(OtherActor))
		{
			if (FFSMManager* fsm = npc->GetState())
			{
				fsm->ChangeState<FStateNpcBeaten>();
			}
		}
	}

	Destroy(this);
}
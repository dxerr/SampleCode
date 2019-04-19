// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectProjectile.h"
#include "GameObject/ActorExtend/ProjectileActor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"


void FGameObjectProjectile::Initialize()
{

}

void FGameObjectProjectile::DeInitialize()
{

}

AActor* FGameObjectProjectile::GetActor()
{
	return Actor;
}

void FGameObjectProjectile::ActorSpawned(AActor* spawn)
{
	FGameObjectBase::ActorSpawned(spawn);
	if (spawn)
	{
		Actor = Cast<AProjectileActor>(spawn);
		//방향 설정
		//필요 하려나??
		UProjectileMovementComponent* projectileComponent = Actor->FindComponentByClass<UProjectileMovementComponent>();
		if (projectileComponent)
		{
			projectileComponent->Velocity = Actor->GetActorForwardVector() * projectileComponent->InitialSpeed;
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectProjectile.h"
#include "GameObject/ActorExtend/ProjectileActor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"


void UGameObjectProjectile::Initialize()
{

}

void UGameObjectProjectile::DeInitialize()
{

}

AActor* UGameObjectProjectile::GetActor()
{
	return Actor;
}

void UGameObjectProjectile::ActorSpawned(AActor* spawn)
{
	UGameObjectBase::ActorSpawned(spawn);
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
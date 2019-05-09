// Fill out your copyright notice in the Description page of Project Settings.

#include "GameObjectProjectile.h"
#include "GameObject/ActorExtend/ProjectileActor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

EGameObjectType UGameObjectProjectile::GetObjectType() const  { return EGameObjectType::Projectile; }
AActor*         UGameObjectProjectile::GetActor() const       { return Actor; }

void UGameObjectProjectile::Initialize()
{
	Super::Initialize();

    SET_FLAG_TYPE(ObjectType, UGameObjectProjectile::GetObjectType());
}

void UGameObjectProjectile::DeInitialize()
{
	Super::DeInitialize();
}

void UGameObjectProjectile::ActorSpawned(AActor* Spawn)
{
	Super::ActorSpawned(Spawn);

	UGameObjectBase::ActorSpawned(Spawn);
	if (Spawn)
	{
		//액터 저장
		Actor = Cast<AProjectileActor>(Spawn);

		//방향 설정
		//필요 하려나??
		UProjectileMovementComponent* projectileComponent = Actor->FindComponentByClass<UProjectileMovementComponent>();
		if (projectileComponent)
		{
			projectileComponent->Velocity = Actor->GetActorForwardVector() * projectileComponent->InitialSpeed;
		}
	}
}
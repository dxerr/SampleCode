// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectSpawner.h"
#include "ObjectCollider.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

FObjectSpawner::FObjectSpawner()
{
	Collider = MakeShareable(new FObjectCollider());
}

FObjectSpawner::~FObjectSpawner()
{
}

void FObjectSpawner::SpawnProjectile(AActor* Owner)
{
	if (UWorld* world = Owner->GetWorld())
	{
		FString path = TEXT("Blueprint'/Game/Blueprints/SpawnObject/BP_ProjectileObject.BP_ProjectileObject'");
		UObject* loadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *path);
		if (loadedObject)
		{
			UBlueprint* castedBlueprint = Cast<UBlueprint>(loadedObject);
			if (castedBlueprint && castedBlueprint->GeneratedClass->IsChildOf(AActor::StaticClass()))
			{
				FVector Pos = Owner->GetActorLocation() + Owner->GetActorForwardVector() * 100.f;
				FRotator Rot(0.f, 0.f, 0.f);
				FActorSpawnParameters SpawnInfo;
				if (AActor* actor = world->SpawnActor(*castedBlueprint->GeneratedClass, &Pos, &Rot, SpawnInfo))
				{
					//임시 생명 주기 설정
					actor->SetLifeSpan(2.f);
					//방향 설정
					UProjectileMovementComponent* projectileComponent = actor->FindComponentByClass<UProjectileMovementComponent>();
					if (projectileComponent)
					{
						projectileComponent->Velocity = Owner->GetActorForwardVector() * projectileComponent->InitialSpeed;
					}

					UE_LOG(LogTemp, Warning, TEXT("Spawn Object spawnpos %f, %f, %f RealPos %f, %f, %f"),
						Pos.X, Pos.Y, Pos.Z,
						actor->GetActorLocation().X, actor->GetActorLocation().Y, actor->GetActorLocation().Z);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("filed LoadObject!!"));
		}
	}
}
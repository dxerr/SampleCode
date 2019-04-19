#include "ObjectSpawner.h"
#include "ObjectCollider.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/ObjectClass/GameObjectProjectile.h"

void UObjectSpawner::Initialize(UWorld* world)
{
	Collider = MakeShareable(new FObjectCollider());
	World = world;
	//World->RemoveOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateRaw(this, &UObjectSpawner::CallbackActorDeSpawn))
}

void UObjectSpawner::DeInitialize()
{
	for (auto el : Spawns)
	{
		el->DeInitialize();
		delete el;
	}

	Spawns.Empty();
	Collider.Reset();
}

void UObjectSpawner::Update(float delta)
{
	for (int i = 0; i != Spawns.Num(); ++i)
	{
		auto el = Spawns[i];
		el->Update(delta);
	}

	/* 
	for (auto el : Spawns)
	{
		el->Update(delta);
	}*/
}

UGameObjectBase* UObjectSpawner::SpawnPlayer(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	UGameObjectLocal* local = NewObject<UGameObjectLocal>();
	local->Initialize();

	if (AActor* actor = local->Spawn(uclass, World, pos, rot))
	{
		Spawns.Add(local);
		actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);
	}
	return local;
}

//[Todo] Class UCharacterMovementComponent
//void UCharacterMovementComponent::FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const
//내부 구현을 참고 하여 개선한다.
UGameObjectBase* UObjectSpawner::SpawnNpc(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	UGameObjectNonPlayer* npc = NewObject<UGameObjectNonPlayer>();
	npc->Initialize();

	FVector rayOri = pos + FVector(0.f, 0.f, 1000.f);
	FVector rayDes = rayOri + FVector(0.f, 0.f, -1.f)  * 1200.f;

	FHitResult HitResult;
	TArray<AActor*> actorsToIgnore;

	//생성도 되기전에 얻어오는게 맞는지 모르것음...
	if (AActor* castActor = uclass->GetDefaultObject<AActor>())
	{
		UKismetSystemLibrary::LineTraceSingle(World, rayOri, rayDes, UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
			false, actorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::Green, FLinearColor::Red);
		if (HitResult.bBlockingHit)
		{
			FVector location = HitResult.Location + FVector(0.f, 0.f, 0.5f);
			if (UCapsuleComponent* Capshule = castActor->FindComponentByClass<UCapsuleComponent>())
			{
				location.Z += Capshule->GetUnscaledCapsuleHalfHeight();
			}

			if (AActor* actor = npc->Spawn(uclass, World, location, rot))
			{
				Spawns.Add(npc);
				actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);
			}
		}
	}

	return npc;
}

UGameObjectBase* UObjectSpawner::SpawnProjectile(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	UGameObjectProjectile* projectile = NewObject<UGameObjectProjectile>();
	projectile->Initialize();

	if (AActor* actor = projectile->Spawn(uclass, World, pos, rot))
	{
		Spawns.Add(projectile);
		actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);
	}
	return projectile;
}

void UObjectSpawner::DespawnObject(UGameObjectBase* despawn)
{
	if (Spawns.Contains(despawn))
	{
		//액터 소멸
		World->DestroyActor(despawn->GetActor());

		//액터 소멸시 일단 관리대상 에서 제거
		RemoveGameObject(despawn);
	}
}

void UObjectSpawner::RemoveGameObject(UGameObjectBase* despawn)
{
	Spawns.Remove(despawn);
}

void UObjectSpawner::CallbackActorDeSpawn(AActor* despawn)
{
	//관리 대상인가 찾음
	UGameObjectBase* findObj = *(Spawns.FindByPredicate([=](UGameObjectBase* el)
	{
		return (el)->GetActor() == despawn;
	}));

	if (findObj) 
	{
		RemoveGameObject(findObj);
	}
}
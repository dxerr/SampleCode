#include "ObjectSpawner.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/ObjectClass/GameObjectProjectile.h"


void UObjectSpawner::Initialize(UWorld* world)
{
	World = world;
	Spawns.Empty();
	AddSpawns.Empty();
	RemoveSpawns.Empty();
	//World->RemoveOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateRaw(this, &UObjectSpawner::CallbackActorDeSpawn))
}

void UObjectSpawner::DeInitialize()
{
	for (auto el : Spawns)
	{
		el->DeInitialize();
		el = NULL;
	}

	for (auto el : AddSpawns)
	{
		el = NULL;
	}

	for (auto el : RemoveSpawns)
	{
		el = NULL;
	}

	World = NULL;
	Spawns.Empty();
	AddSpawns.Empty();
	RemoveSpawns.Empty();
}

UGameObjectBase* UObjectSpawner::FindObject(AActor* Actor)
{
	auto findobj = Spawns.FindByPredicate([=](UGameObjectBase* el)
	{
		AActor* a = el->GetActor();
		return NULL != a && a == Actor;
	});

	return findobj ? *findobj : NULL;
}

void UObjectSpawner::Update(float Delta)
{
	//대상 리스트 제거
	if (0 < RemoveSpawns.Num())
	{
		for (auto el : RemoveSpawns)
		{
			Spawns.RemoveSwap(el);
		}
		RemoveSpawns.Empty();
	}

	//대상 추가
	if (0 < AddSpawns.Num())
	{
		Spawns.Append(AddSpawns);
		AddSpawns.Empty();
	}

	for (auto el : Spawns)
	{
		el->Update(Delta);
	}
}

UGameObjectBase* UObjectSpawner::SpawnPlayer(UClass* Uclass, const FVector& Pos, const FRotator& Rot)
{
	UGameObjectBase* local = NewObject<UGameObjectLocal>();
	local->Initialize();

	if (auto actor = local->Spawn(Uclass, World, Pos, Rot))
	{
		AddSpawns.Add(local);
		actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);
	}
	return local;
}

//[Todo] Class UCharacterMovementComponent
//void UCharacterMovementComponent::FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const
//내부 구현을 참고 하여 개선한다.
UGameObjectBase* UObjectSpawner::SpawnNpc(UClass* Uclass, const FVector& Pos, const FRotator& Rot)
{
	UGameObjectNonPlayer* npc = NewObject<UGameObjectNonPlayer>();
	npc->Initialize();

	FVector rayOri = Pos + FVector(0.f, 0.f, 1000.f);
	FVector rayDes = rayOri + FVector(0.f, 0.f, -1.f)  * 1200.f;

	FHitResult HitResult;
	TArray<AActor*> actorsToIgnore;

	//생성도 되기전에 얻어오는게 맞는지 모르것음...
	if (AActor* castActor = Uclass->GetDefaultObject<AActor>())
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

			if (auto actor = npc->Spawn(Uclass, World, location, Rot))
			{
				AddSpawns.Add(npc);
				actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);
			}
		}
	}

	return npc;
}

UGameObjectBase* UObjectSpawner::SpawnProjectile(UClass* Uclass, const FVector& Pos, const FRotator& Rot)
{
	UGameObjectProjectile* projectile = NewObject<UGameObjectProjectile>();
	projectile->Initialize();

	if (auto actor = projectile->Spawn(Uclass, World, Pos, Rot))
	{
		AddSpawns.Add(projectile);
		actor->OnDestroyed.AddDynamic(this, &UObjectSpawner::CallbackActorDeSpawn);

		//충돌 처리
		if (UPrimitiveComponent* collider = actor->FindComponentByClass<UPrimitiveComponent>())
		{
			collider->OnComponentHit.AddDynamic(this, &UObjectSpawner::CallbackCompHit);
		}
	}
	return projectile;
}

void UObjectSpawner::DespawnObject(UGameObjectBase* Despawn)
{
	if (Spawns.Contains(Despawn))
	{
		//액터 소멸
		World->DestroyActor(Despawn->GetActor());

		//액터 소멸시 일단 관리대상 에서 제거
		RemoveGameObject(Despawn);
	}
}

void UObjectSpawner::RemoveGameObject(UGameObjectBase* Despawn)
{
	RemoveSpawns.Add(Despawn);
}

void UObjectSpawner::CallbackCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		//충돌 객체 성향에 따라 Destory여부 설정하기
		auto hitObj = FindObject(Cast<AActor>(HitComponent));
		if (hitObj)
		{
			//현재는 무조건 삭제
			DespawnObject(hitObj);
		}

		//피격 알림
		if (auto findObj = FindObject(OtherActor))
		{
			findObj->OnHit(hitObj);
		}
	}
}

void UObjectSpawner::CallbackActorDeSpawn(AActor* Despawn)
{
	//관리 대상인가 찾음
	if (auto findObj = FindObject(Despawn))
	{
		RemoveGameObject(findObj);
	}
}
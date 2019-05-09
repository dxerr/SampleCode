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
	TypeSpawns.Empty(EGameObjectTypeALLCount);
	//타입별 빈공간 생성
	for (auto el : EGameObjectTypeALL)
	{
		TypeSpawns.Emplace(el);
	}

	//World->RemoveOnActorSpawnedHandler(FOnActorSpawned::FDelegate::CreateRaw(this, &UObjectSpawner::CallbackActorDeSpawn))
}

void UObjectSpawner::DeInitialize()
{
	for (auto el : Spawns)
	{
		el->DeInitialize();
	}

	World = NULL;
	TypeSpawns.Empty();
	AddSpawns.Empty();
	RemoveSpawns.Empty();
	Spawns.Empty();
}

UGameObjectBase* UObjectSpawner::FindObject(AActor* Actor, EGameObjectType Type)
{
	if (Type == EGameObjectType::Base)
	{
		if (auto findobj = Spawns.FindByPredicate([=](UGameObjectBase* el)
		{
			AActor* a = el->GetActor();
			return NULL != a && a == Actor;
		}))
		{
			return *findobj;
		}
	}
	else
	{
		auto list = TypeSpawns[Type];
		if (auto findobj = list.FindByPredicate([=](UGameObjectBase* el)
		{
			AActor* a = el->GetActor();
			return NULL != a && a == Actor;
		}))
		{
			return *findobj;
		}
	}

	return NULL;
}

UGameObjectBase* UObjectSpawner::FindObject(EGameObjectType Type)
{
    return TypeSpawns[Type].Num() > 0 ? TypeSpawns[Type].Top() : NULL;
}

TArray<UGameObjectBase*> UObjectSpawner::FindObjects(EGameObjectType Type)
{
	return TypeSpawns[Type];
}

void UObjectSpawner::Update(float Delta)
{
	//대상 리스트 제거
	UpdateRemoveGameObject();
	//대상 추가
	UpdateAddGameObject();

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
		AddSpawns.Emplace(local);
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
				AddSpawns.Emplace(npc);

                //액터 자동 소멸 콜백을 연결하여 관리 대상 동기화를 맞춤
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
		AddSpawns.Emplace(projectile);
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
		RemoveSpawns.Emplace(Despawn);
	}
}

void UObjectSpawner::UpdateAddGameObject()
{
	//대상 추가
	if (0 < AddSpawns.Num())
	{
		for (auto el : AddSpawns)
		{
			uint8 key = el->GetObjectTypeMask();
			for (auto el2 : EGameObjectTypeALL)
			{
				if (CHECK_FLAG_TYPE(key, el2))
				{
					TypeSpawns[el2].Emplace(el);
				}
			}
			Spawns.Emplace(el);
		}
		AddSpawns.Empty();
	}
}

void UObjectSpawner::UpdateRemoveGameObject()
{
	if (0 < RemoveSpawns.Num())
	{
		for (auto el : RemoveSpawns)
		{
			uint8 key = el->GetObjectTypeMask();
			for (auto el2 : EGameObjectTypeALL)
			{
				if (CHECK_FLAG_TYPE(key, el2))
				{
					TypeSpawns[el2].RemoveSwap(el);
				}
			}

			Spawns.RemoveSwap(el);
		}
		RemoveSpawns.Empty();
	}
}

void UObjectSpawner::CallbackCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		UGameObjectBase* hitObj = FindObject(HitComponent->GetOwner(), EGameObjectType::Projectile);
		//피격 알림
		if (UGameObjectBase* findObj = FindObject(OtherActor, EGameObjectType::NonPlayer))
		{
			findObj->OnHit(hitObj);
		}

		if (hitObj)
		{
			//충돌 객체 성향에 따라 Destory여부 설정하기
			//현재는 무조건 삭제
			DespawnObject(hitObj);
		}
	}
}

void UObjectSpawner::CallbackActorDeSpawn(AActor* Despawn)
{
	//관리 대상인가 찾음
	if (auto findObj = FindObject(Despawn))
	{
		RemoveSpawns.Emplace(findObj);
	}
}
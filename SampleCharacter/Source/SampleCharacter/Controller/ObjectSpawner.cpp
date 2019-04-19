#include "ObjectSpawner.h"
#include "ObjectCollider.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"
#include "GameObject/ObjectClass/GameObjectNonPlayer.h"
#include "GameObject/ObjectClass/GameObjectProjectile.h"

FObjectSpawner::FObjectSpawner()
{
	Collider = MakeShareable(new FObjectCollider());
}

void FObjectSpawner::Initialize(UWorld* world)
{
	World = world;
}

void FObjectSpawner::DeInitialize()
{
	for (auto el : Spawns)
	{
		el->DeInitialize();
		delete el;
	}

	Spawns.Empty();
	Collider.Reset();
}

void FObjectSpawner::Update(float delta)
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

FGameObjectBase* FObjectSpawner::SpawnPlayer(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	FGameObjectLocal* local = new FGameObjectLocal();
	local->Initialize();

	if (AActor* actor = local->Spawn(uclass, World, pos, rot))
	{
		Spawns.Add(local);
	}
	else
	{
		delete local;
	}

	return local;
}

//[Todo] Class UCharacterMovementComponent
//void UCharacterMovementComponent::FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const
//내부 구현을 참고 하여 개선한다.
FGameObjectBase* FObjectSpawner::SpawnNpc(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	FGameObjectNonPlayer* npc = new FGameObjectNonPlayer();
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
			}
			else
			{
				delete npc;
			}
		}
	}

	return npc;
}

FGameObjectBase* FObjectSpawner::SpawnProjectile(UClass* uclass, const FVector& pos, const FRotator& rot)
{
	FGameObjectProjectile* projectile = new FGameObjectProjectile();
	projectile->Initialize();

	if (AActor* actor = projectile->Spawn(uclass, World, pos, rot))
	{
		Spawns.Add(projectile);
	}
	else
	{
		delete projectile;
	}

	return projectile;
}
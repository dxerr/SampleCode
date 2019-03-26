// Fill out your copyright notice in the Description page of Project Settings.

#include "NonePcObject.h"
#include "Component/Animation/AnimInstanceState.h"
#include "State/FSMManager.h"
#include "State/StateNPC.h"

ANonePcObject::ANonePcObject()
{
	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(TEXT("NpckeletalMesh"));
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		//Mesh->SetupAttachment(CapsuleComponent);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	RootComponent = Mesh;
}

void ANonePcObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Animation = Cast<UAnimInstanceState>(Mesh->GetAnimInstance());
	if (!Fsm)
	{
		Fsm = new FFSMManager();
		Fsm->Initialize(this);
	}
}

// Called when the game starts or when spawned
void ANonePcObject::BeginPlay()
{
	Super::BeginPlay();

	Fsm->ChangeState<FStateNpcIdle>();
}
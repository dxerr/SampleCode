#include "GameObjectLocal.h"
#include "GameObject/ActorExtend/LocalCharacter.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/Parts/PartsLocal.h"
#include "GameObject/State/StateLocal.h"
#include "Controller/PlayerControllerExpend.h"
#include "GameInstanceExtend.h"
#include "Controller/Input/InputBindingLocalPlayer.h"

#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

void UGameObjectLocal::Initialize()
{
	Super::Initialize();

	Fsm = new FFSMManager();
	Fsm->Initialize(this);

	UpperFsm = new FFSMManager();
	UpperFsm->Initialize(this);
	Actor = NULL;
}
void UGameObjectLocal::DeInitialize()
{
	Super::DeInitialize();

	if (Actor)
	{
		Actor->GetWorld()->DestroyActor(Actor);
	}

	if (Fsm)		{ delete Fsm; }
	if (UpperFsm)	{ delete UpperFsm; }
	if (Skill)		{ delete Skill; }
	if (Parts)		{ delete Parts; }
}

AActor* UGameObjectLocal::GetActor()
{
	return GetLocal();
}

ACharacter* UGameObjectLocal::GetCharacter()
{
	return GetLocal();
}

ALocalCharacter* UGameObjectLocal::GetLocal()
{
	return Actor;
}

FFSMManager* UGameObjectLocal::GetBaseFSM()
{
	return Fsm;
}

FFSMManager* UGameObjectLocal::GetUpperFSM()
{
	return UpperFsm;
}

FSkillBase* UGameObjectLocal::GetSkill()
{
	return Skill;
}

FPartsBase* UGameObjectLocal::GetParts()
{
	return Parts;
}

void UGameObjectLocal::ActorSpawned(AActor* Spawn)
{
	Super::ActorSpawned(Spawn);

	if (Spawn)
	{
		Actor = Cast<ALocalCharacter>(Spawn);

		//키입력 바인딩
		Actor->GetInputBinder()->Initialize(this);
	}

	Skill = new FSKillLocal();
	Skill->Initialize(this);
	Skill->LoadData(TEXT("SkillDataContainerBase'/Game/Resource/DataAsset/LocalSkills.LocalSkills'"));

	Parts = new FPartsLocal();
	Parts->Initialize(this);
	Parts->LoadData(TEXT("PartsDataContainerBase'/Game/Resource/DataAsset/LocalParts.LocalParts'"));

	//모든 파츠 장착
	Parts->AttachAll();

	//기본 상태 설정
	Fsm->ChangeState<FStateIdle>();
}

void UGameObjectLocal::Update(float delta)
{
	Super::Update(delta);

	if (UpperFsm) { UpperFsm->Update(this, delta); }
}
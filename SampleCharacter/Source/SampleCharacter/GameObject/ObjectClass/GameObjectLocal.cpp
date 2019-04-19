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

void FGameObjectLocal::Initialize()
{
	Fsm = new FFSMManager();
	Fsm->Initialize(this);

	UpperFsm = new FFSMManager();
	UpperFsm->Initialize(this);
	Actor = NULL;
}
void FGameObjectLocal::DeInitialize()
{
	if (Actor)
	{
		Actor->GetWorld()->DestroyActor(Actor);
	}
}

AActor* FGameObjectLocal::GetActor()
{
	return GetLocal();
}

ACharacter* FGameObjectLocal::GetCharacter()
{
	return GetLocal();
}

ALocalCharacter* FGameObjectLocal::GetLocal()
{
	return Actor;
}

FFSMManager* FGameObjectLocal::GetBaseFSM()
{
	return Fsm;
}

FFSMManager* FGameObjectLocal::GetUpperFSM()
{
	return UpperFsm;
}

FSkillBase* FGameObjectLocal::GetSkill()
{
	return Skill;
}

FPartsBase* FGameObjectLocal::GetParts()
{
	return Parts;
}

void FGameObjectLocal::ActorSpawned(AActor* Spawn)
{
	FGameObjectPlayer::ActorSpawned(Spawn);
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
}

void FGameObjectLocal::Update(float delta)
{
	FGameObjectPlayer::Update(delta);
	if (UpperFsm) { UpperFsm->Update(delta); }
}
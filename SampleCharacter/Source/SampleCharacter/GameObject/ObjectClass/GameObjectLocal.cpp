#include "GameObjectLocal.h"
#include "GameObject/ActorExtend/LocalCharacter.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/Skill/SKillLocal.h"
#include "GameObject/Parts/PartsLocal.h"
#include "GameObject/State/StateLocal.h"
#include "GameObject/Movement/MovementLocal.h"
#include "GameInstanceExtend.h"
#include "Controller/Input/InputBindingLocalPlayer.h"

#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"

//프로퍼티
EGameObjectType UGameObjectLocal::GetObjectType() const { return EGameObjectType::LocalPlayer; }
AActor*			UGameObjectLocal::GetActor() const	    { return GetLocal(); }
ALocalCharacter* UGameObjectLocal::GetLocal() const     { return Actor; }
FFSMManager*	UGameObjectLocal::GetBaseFSM() const    { return Fsm; }
FFSMManager*	UGameObjectLocal::GetUpperFSM() const   { return UpperFsm; }
FSkillBase*		UGameObjectLocal::GetSkill() const      { return Skill; }
FPartsBase*		UGameObjectLocal::GetParts() const      { return Parts; }
//

void UGameObjectLocal::Initialize()
{
	Super::Initialize();

    SET_FLAG_TYPE(ObjectType, UGameObjectLocal::GetObjectType());

	Fsm = new FFSMManager();
	Fsm->Initialize(this);

	UpperFsm = new FFSMManager();
	UpperFsm->Initialize(this);

	Actor = NULL;
}

void UGameObjectLocal::DeInitialize()
{
	Super::DeInitialize();
}

void UGameObjectLocal::ActorSpawned(AActor* Spawn)
{
	Super::ActorSpawned(Spawn);

	if (Spawn)
	{
		//액터 저장
		Actor = Cast<ALocalCharacter>(Spawn);

		//키입력 바인딩
		Actor->GetInputBinder()->Initialize(this);

        Movement = new FMovementLocal();
        Movement->Initialize(this);

        Skill = new FSKillLocal();
        Skill->Initialize(this);
        //임시 데이터 적용
        Skill->LoadData(TEXT("SkillDataContainerBase'/Game/Resource/DataAsset/LocalSkills.LocalSkills'"));

        Parts = new FPartsLocal();
        Parts->Initialize(this);
        //임시 데이터 적용
        Parts->LoadData(TEXT("PartsDataContainerBase'/Game/Resource/DataAsset/LocalParts.LocalParts'"));

        //기본 상태 설정
        Fsm->ChangeState<FStateSpawn>();

        //모든 파츠 장착
        Parts->AttachAll();
	}
}

void UGameObjectLocal::Update(float delta)
{
	Super::Update(delta);

	if (UpperFsm) { UpperFsm->Update(this, delta); }
}
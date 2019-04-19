// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillLocal.h"
#include "Container/SkillDataContainerBase.h"
#include "Process/SKillActionNodeProjectile.h"
#include "GameObject/State/FSMManager.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"


FSKillLocal::FSKillLocal()
{
}

FSKillLocal::~FSKillLocal()
{
}

void FSKillLocal::Initialize(UGameObjectBase* owner)
{
	FSkillBase::Initialize(owner);
}

TArray<FSkillActionNodeBase*>* FSKillLocal::GetSKillNodes(int ID)
{
	return MapSkillNodes.Find(ID);
}

void FSKillLocal::LoadData(const TCHAR * Path)
{
	FSkillBase::LoadData(Path);
	LoadSKillNode();
}

void FSKillLocal::UseSKill(int ID)
{
	FSkillBase::UseSKill(ID);

	//스킬 상태로 전환
	UGameObjectLocal* My = Cast<UGameObjectLocal>(Owner);
	FFSMManager* fsm = My->GetUpperFSM();
	fsm->ChangeState<FStateAttack>();
}

void FSKillLocal::LoadSKillNode()
{
	MapSkillNodes.Empty();
	for (auto el : SkillFactory->GetSkillData())
	{
		for (auto el2 : el.SkillAction)
		{
			FSkillActionNodeBase* NodeData = CreateSkillNode(el2);
			if (NodeData)
			{
				NodeData->Process(Owner);
				TArray<FSkillActionNodeBase*>* findList = MapSkillNodes.Find(el.ID);
				if (findList)
				{
					findList->Push(NodeData);
				}
				else
				{
					TArray<FSkillActionNodeBase*> nodeList;
					nodeList.Add(NodeData);
					MapSkillNodes.Add(el.ID, nodeList);
				}
			}
		}
	}
}

FSkillActionNodeBase* FSKillLocal::CreateSkillNode(const FSkillActionDataBase& Data) const
{
	switch (Data.Type)
	{
	case 1:
		return new FSKillActionNodeProjectile(Data);
	}

	return nullptr;
}

void FSKillLocal::OnSKillNode()
{
	FSkillBase::OnSKillNode();

	if (CurrentSkillData)
	{
		RunSkillNodes.Empty();
		RunSkillNodes.Append(*GetSKillNodes(CurrentSkillData->Data->ID));
	}
}

void FSKillLocal::RunSkillNode(float DeltaTime)
{
	FSkillBase::RunSkillNode(DeltaTime);

	//실행할 노드 찾기

	for (auto el : RunSkillNodes)
	{
		if (el->GetRate() < CurrentSkillData->GetRate())
		{
			UE_LOG(LogTemp, Warning, TEXT("SkillAction node rate %f Skill Rate %f"), el->GetRate(), CurrentSkillData->GetRate());

			el->Action(Owner);
			//사용 스킬로 이전
			UseSkillNodes.Add(el);
			//실행 스킬에서 제거
			RunSkillNodes.Remove(el);
			break; //계속 검사해야된다면 iterator로 처리
		}
	}

	//사용 스킬 감시/제거
	UGameObjectBase* param = Owner;
	UseSkillNodes.RemoveAll([param](FSkillActionNodeBase* el)
	{
		return el->Update(param);
	});

	//스킬 종료
	if (CurrentSkillData->IsEnd())
	{
		//유휴 상태로 전환
		UGameObjectLocal* My = Cast<UGameObjectLocal>(Owner);
		FFSMManager* fsm = My->GetUpperFSM();
		fsm->ChangeState<FStateUpperIdle>();
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "SKillLocal.h"
#include "Container/SkillDataContainerBase.h"
#include "Process/SKillActionNodeProjectile.h"
#include "SpawnObject/Child/LocalPlayerObject.h"
#include "SpawnObject/Child/State/FSMManager.h"
#include "SpawnObject/Child/State/StateLocal.h"

FSKillLocal::FSKillLocal()
{
}

FSKillLocal::~FSKillLocal()
{
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

	//��ų ���·� ��ȯ
	ALocalPlayerObject* My = static_cast<ALocalPlayerObject*>(Owner->cast());
	FFSMManager* fsm = My->GetUpperState();
	fsm->ChangeState<FStateAttack>();
}

void FSKillLocal::LoadSKillNode()
{
	MapSkillNodes.Empty();
	for (auto el : SkillFactory->GetSkillData())
	{
		for (auto el2 : el.SkillAction)
		{
			FSkillActionNodeBase* NodeData = CreateSkillNode(&el2);
			if (nullptr != NodeData)
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

FSkillActionNodeBase* FSKillLocal::CreateSkillNode(const FSkillActionDataBase* Data)
{
	switch (Data->Type)
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

	//������ ��� ã��

	for (auto el : RunSkillNodes)
	{
		if (el->GetRate() < CurrentSkillData->GetRate())
		{
			el->Action(Owner);
			//��� ��ų�� ����
			UseSkillNodes.Add(el);
			//���� ��ų���� ����
			RunSkillNodes.Remove(el);
			break; //��� �˻��ؾߵȴٸ� iterator�� ó��
		}
	}

	//��� ��ų ����/����
	FBaseObject* param = Owner;
	UseSkillNodes.RemoveAll([param](FSkillActionNodeBase* el)
	{
		return el->Update(param);
	});

	//��ų ����
	if (CurrentSkillData->IsEnd())
	{
		//���� ���·� ��ȯ
		ALocalPlayerObject* My = static_cast<ALocalPlayerObject*>(Owner->cast());
		FFSMManager* fsm = My->GetUpperState();
		fsm->ChangeState<FStateUpperIdle>();
	}
}
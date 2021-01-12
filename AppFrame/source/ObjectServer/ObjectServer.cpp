
#include "DxLib.h"
#include "ObjectServer.h"

ObjectServer::ObjectServer()
{
	_vObject.clear();
	_vDel.clear();
}

ObjectServer::~ObjectServer()
{
	Clear();
}

// ���X�g�ɓo�^����Ă���I�u�W�F�N�g�����ׂď���
void ObjectServer::Clear()
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		delete(*ite);
	}
	_vObject.clear();
}

// ���X�g�ɃI�u�W�F�N�g��o�^����
void ObjectServer::Add(ObjectBase* obj)
{
	_vObject.push_back(obj);
}

// �w��̃I�u�W�F�N�g���폜����
void ObjectServer::Del(ObjectBase* obj)
{
	_vDel.push_back(obj);
}

// Del���X�g�̃I�u�W�F�N�g���폜����
void ObjectServer::DelListObjects()
{
	for (auto iteDel = _vDel.begin(); iteDel != _vDel.end(); ++iteDel)
	{
		for (auto ite = _vObject.begin(); ite != _vObject.end();)
		{
			if ((*ite) == (*iteDel))
			{
				delete(*ite);
				ite = _vObject.erase(ite);
			}
			else
			{
				ite++;
			}
		}
	}
	_vDel.clear();
}

// Process()��o�^���ɉ�
void ObjectServer::Process()
{
	// Process()���Ăяo��
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Process();
	}

	// Del���X�g�ɂ���I�u�W�F�N�g�����X�g����폜����
	DelListObjects();
}

// Draw()��o�^���ɉ�
void ObjectServer::Render()
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Render();
	}
}

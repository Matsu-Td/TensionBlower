#include "ApplicationMain.h"
#include "BulletServer.h"

BulletServer::BulletServer()
{
	_v.clear();
	_vAdd.clear();
	_vDel.clear();
//	_updateProc = false;
}

BulletServer::~BulletServer()
{
//	_updateProc = false;
	Clear();
}

void BulletServer::Clear()
{
	for (auto ite = _v.begin(); ite != _v.end(); ite++)
	{
		delete (*ite);
	}
	_v.clear();
}

void BulletServer::Del(BulletBase* bullet) {
	_vDel.push_back(bullet);
}

void BulletServer::Add(BulletBase* bullet)
{
	_vAdd.push_back(bullet);
}

// Add���X�g�̃I�u�W�F�N�g��ǉ�����
void BulletServer::AddListBullet()
{
	for (auto iteAdd = _vAdd.begin(); iteAdd != _vAdd.end(); iteAdd++)
	{
		_v.push_back((*iteAdd));
	}
	_vAdd.clear();
}

// Del���X�g�̃I�u�W�F�N�g���폜����
void	BulletServer::DelListBullet()
{
	for (auto iteDel = _vDel.begin(); iteDel != _vDel.end(); iteDel++)
	{
		for (auto ite = _v.begin(); ite != _v.end();)
		{
			if ((*ite) == (*iteDel))
			{
				delete (*ite);
				ite = _v.erase(ite);
			}
			else
			{
				ite++;
			}
		}
	}
	_vDel.clear();
}
void	BulletServer::Update() {

	// Add���X�g�ɂ���I�u�W�F�N�g�����X�g�ɓo�^����
	AddListBullet();

	// Update�Ăяo���i���̒��ŌĂ΂ꂽAdd/Del�͒ǉ����X�g�A�폜���X�g�ɓo�^�����j
	for (auto ite = _v.begin(); ite != _v.end(); ite++) {
		(*ite)->Update();
	}

	// Del���X�g�ɂ���I�u�W�F�N�g�����X�g����폜����
	DelListBullet();
}


void BulletServer::Render() {
	for (auto ite = _v.begin(); ite != _v.end(); ite++) {
		(*ite)->Render();
	}
	DrawFormatString(0, 400, GetColor(255, 0, 0), "  playerBullet�T�C�Y    = %d", _v.size());
}
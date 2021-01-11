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

// Addリストのオブジェクトを追加する
void BulletServer::AddListBullet()
{
	for (auto iteAdd = _vAdd.begin(); iteAdd != _vAdd.end(); iteAdd++)
	{
		_v.push_back((*iteAdd));
	}
	_vAdd.clear();
}

// Delリストのオブジェクトを削除する
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

	// Addリストにあるオブジェクトをリストに登録する
	AddListBullet();

	// Update呼び出し（この中で呼ばれたAdd/Delは追加リスト、削除リストに登録される）
	for (auto ite = _v.begin(); ite != _v.end(); ite++) {
		(*ite)->Update();
	}

	// Delリストにあるオブジェクトをリストから削除する
	DelListBullet();
}


void BulletServer::Render() {
	for (auto ite = _v.begin(); ite != _v.end(); ite++) {
		(*ite)->Render();
	}
	DrawFormatString(0, 400, GetColor(255, 0, 0), "  playerBulletサイズ    = %d", _v.size());
}
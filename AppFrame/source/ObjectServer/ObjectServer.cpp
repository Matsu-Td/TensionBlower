
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

// リストに登録されているオブジェクトをすべて消す
void ObjectServer::Clear()
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		delete(*ite);
	}
	_vObject.clear();
}

// リストにオブジェクトを登録する
void ObjectServer::Add(ObjectBase* obj)
{
	_vObject.push_back(obj);
}

// 指定のオブジェクトを削除する
void ObjectServer::Del(ObjectBase* obj)
{
	_vDel.push_back(obj);
}

// Delリストのオブジェクトを削除する
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

// Process()を登録順に回す
void ObjectServer::Process()
{
	// Process()を呼び出し
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Process();
	}

	// Delリストにあるオブジェクトをリストから削除する
	DelListObjects();
}

// Draw()を登録順に回す
void ObjectServer::Render()
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Render();
	}
}

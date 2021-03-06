/**
 * @file  ObjectServer.cpp
 * @brief オブジェクト管理サーバー
 *
 * @date 2021/03/20
 */

#include "DxLib.h"
#include "ObjectServer.h"

using namespace tensionblower::object;

ObjectServer::ObjectServer() {

	_vObject.clear();
	_vAdd.clear();
	_vDel.clear();
}

ObjectServer::~ObjectServer() {

	Clear();
}

/*
 * リストに登録されているオブジェクトを全て削除
 */
void ObjectServer::Clear() {

	for (auto&& itr : _vObject) {
		delete itr;
	}
	_vObject.clear();
}

/*
 * Addリストにオブジェクトを追加する
 */
void ObjectServer::Add(ObjectBase* obj) {

	_vAdd.push_back(obj);
}

/*
 * Delリストにオブジェクトを追加する
 */
void ObjectServer::Del(ObjectBase* obj) {

	_vDel.push_back(obj);
}

/*
 * Addリストのオブジェクトを追加する
 */
void ObjectServer::AddListObjects() {

	for (auto&& itrAdd : _vAdd) {
		_vObject.push_back(itrAdd);
	}
	_vAdd.clear();
}

/*
 * Delリストのオブジェクトを追加する
 */
void ObjectServer::DelListObjects() {

	for (auto&& itrDel : _vDel) {
		for (auto itr = _vObject.begin(); itr != _vObject.end();) {
			if ((*itr) == itrDel) {
				delete (*itr);
				itr = _vObject.erase(itr);
			}
			else {
				itr++;
			}
		}
	}
	_vDel.clear();
}

/*
 * 登録したオブジェクトのProcess()を登録順に回す
 */
void ObjectServer::Process() {
	// Addリストにあるオブジェクトをリストに登録する
	AddListObjects();

	// Process()を呼び出し
	for (auto&& itr : _vObject) {
		itr->Process();
	}

	// Delリストにあるオブジェクトをリストから削除する
	DelListObjects();
}

/*
 * 登録したオブジェクトのRender()を登録順に回す
 */
void ObjectServer::Render() {

	for (auto&& itr : _vObject) {
		itr->Render();
	}
}
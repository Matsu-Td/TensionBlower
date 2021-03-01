#pragma once

/**
 * @file ObjectServer.h
 * @brief オブジェクト管理サーバー
 * 
 * @date 2021-01-15
 */

#include <vector>
#include "ObjectBase.h"

class ObjectServer {
public:
	ObjectServer();
	~ObjectServer();

	/**
	 * @brief 登録したオブジェクトのProcess()を登録順に回す
	 */
	void Process();

	/**
	 * @brief 登録したオブジェクトの Render()を登録順に回す
	 */
	void Render();

	/**
	 * @brief Addリストにオブジェクトを追加する
	 */
	void Add(ObjectBase* obj);

	/**
	 * @brief Delリストにオブジェクトを追加する
	 */
	void Del(ObjectBase* obj);

	/**
	 * @brief リストに登録されているオブジェクトを全て削除
	 */
	void Clear();

	/**
	 * @brief  _vObjectリストを戻り値として返す 
	 * @return _vObjectリスト
	 */
	std::vector<ObjectBase*>* List() { return &_vObject; }

private:
	/**
	 * @brief Addリストのオブジェクトを追加する
	 */
	void AddListObjects();

	/**
	 * @brief Delリストのオブジェクトを追加する
	 */
	void DelListObjects();

protected:
	std::vector<ObjectBase*> _vObject; // ObjectBaseを登録するリスト
	std::vector<ObjectBase*> _vAdd;    // 追加するオブジェクトリスト
	std::vector<ObjectBase*> _vDel;	   // 削除するオブジェクトリスト
};

#pragma once
#include <vector>
#include "ObjectBase.h"

class ObjectServer {
public:
	ObjectServer();
	~ObjectServer();

	void Process();
	void Render();
	void Add(ObjectBase* obj);
	void Del(ObjectBase* obj);
	void Clear();

	std::vector<ObjectBase*>* List() { return &_vObject; }

private:
	void AddListObjects();
	void DelListObjects();

protected:
	std::vector<ObjectBase*> _vObject; //ObjectBaseを登録するリスト
	std::vector<ObjectBase*> _vAdd;
	std::vector<ObjectBase*> _vDel;	// 削除するオブジェクトリスト
};

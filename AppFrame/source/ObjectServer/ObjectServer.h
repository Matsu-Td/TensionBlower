#pragma once
#include	<vector>
#include	"ObjectBase.h"

// オブジェクトサーバー
class ObjectServer {
public:
	ObjectServer();
	~ObjectServer();

	void	Clear();
	void	Add(ObjectBase* obj);
	void	Del(ObjectBase* obj);

	void	Update();
	void	Render();

	std::vector<ObjectBase*>* List() { return &_vObject; }

private:
	void	AddListObjects();
	void	DelListObjects();

protected:
	std::vector<ObjectBase*>	_vObject;		// ObjectBaseを登録するリスト

	std::vector<ObjectBase*>	_vAdd;	// 追加するオブジェクトリスト
	std::vector<ObjectBase*>	_vDel;	// 削除するオブジェクトリスト


};

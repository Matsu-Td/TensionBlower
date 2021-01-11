#pragma once

#include "appframe.h"
#include "BulletBase.h"
#include <list>

class BulletServer {
public:
	BulletServer();
    ~BulletServer();

	void Update();
	void Render();
	void Add(BulletBase* bullet);
	void Del(BulletBase* bullet);
	void Clear();
	std::vector<BulletBase*>* List() { return &_v; }

private:
	void AddListBullet();
	void DelListBullet();

protected:
	std::vector<BulletBase*> _v;
	std::vector<BulletBase*> _vAdd;
	std::vector<BulletBase*> _vDel;
//	bool _updateProc;
};

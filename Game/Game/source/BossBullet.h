#pragma once
#include "appframe.h"

class BossBullet {
public:
	BossBullet();
	virtual ~BossBullet();

	void Initialize();
	void Process();
	void Render();

	static BossBullet* GetInstance() { return _pInstance; }
	VECTOR GetPos() { return _vPos; }
	VECTOR GetScrnPos(){ return _scrnPos; }

	static BossBullet* _pInstance;

private:
	int _mh;
	VECTOR _vPos;   // �ʒu
	VECTOR _vDir;   // ����
	VECTOR _scrnPos;
};
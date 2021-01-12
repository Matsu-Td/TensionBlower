#pragma once
#include "appframe.h"
#include "BossBullet.h"

class Boss : public ObjectBase{
public:
	Boss();
	~Boss();
	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }
	void Initialize();
	void Process();
	void Render();

	static Boss* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }

	static Boss* _pInstance;

private:
	int _mh;
	VECTOR _vPos;
	VECTOR _vDir;   // Œü‚«


	int _attachIndex;
	float _totalTime;
	float _playTime;

	int _shotCnt;
	int _mlsCnt;
	float _shotAngle;
	float shotInterval;
//	BossBullet _bsBullet;
};

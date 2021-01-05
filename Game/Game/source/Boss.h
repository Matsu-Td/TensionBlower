#pragma once
#include "appframe.h"
#include "BossBullet.h"

class Boss
{
public:
	Boss();
	~Boss();

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

	BossBullet _bsBullet;
};

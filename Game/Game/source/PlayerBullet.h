#pragma once
#include "appframe.h"

class PlayerBullet {
public:
	PlayerBullet();
	~PlayerBullet();

	void Initialize();
	void Process();
	void Render();

private:
	int _mh;
	VECTOR _vPos;
	//float _moveSpd;
	float _shotAngle;
	float _vx, _vz;
	bool _shotFlag;
};
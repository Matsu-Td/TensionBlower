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
	int    _mh;           // ���f���n���h��
	VECTOR _vPos;         // ���W
	float  _shotAngle;    // �e�𔭎˂���p�x
	bool   _shotFlag;     // ���˃t���O

	static constexpr int MAX_BULLETS = 100; // ���e���ő�
};
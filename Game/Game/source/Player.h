#pragma once
#include "appframe.h"
#include "PlayerBullet.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize();
	void Process();
	void Render();

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetDir() const { return _vDir; }

	static Player* _pInstance;

	int _mh;

	static constexpr float GROUND_Y = 0.f;  // �n���Y���W

private:
	int _mhMap;
	VECTOR _vPos;   // �ʒu
	VECTOR _oldPos;
	VECTOR _vDir;   // ����
	VECTOR _capsulePos1, _capsulePos2; // �����蔻��p�J�v�Z��
	//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _mvSpd;
	bool _isCharging;
	bool _hit;     // �f�o�b�O�̂�

	// �W�����v�֌W
	float _inVel;      // �����x
	float  _jumpTime;  // �W�����v���Ԑ���
	bool _isCanJump;   // �W�����v��(true:��, false:�s��)

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		DASH,
		JUMP,
		CHARGE,
	};
	STATE _state; // �v���C���[�̏��

	PlayerBullet _bullet;
};
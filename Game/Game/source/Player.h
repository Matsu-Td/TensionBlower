#pragma once
#include "appframe.h"


class Player
{
public:
	Player();
	~Player();

	void Initialize();
	void Process();
	void Render();

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() { return _vPos; }

	static Player* _pInstance;

	int _mh;
private:
	const float GROUND_Y = 0.f;  // ����Y���W

	
	int _mhMap;
	VECTOR _vPos;   // �ʒu
	VECTOR _oldPos;
	VECTOR _vDir;   // ����
	VECTOR _capsulePos1, _capsulePos2; // �����蔻��p�J�v�Z��
	//MV1_COLL_RESULT_POLY_DIM _hitPolyDim;

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _vel;
	bool _isCanJump;
	bool _hit;     // �f�o�b�O�̂�

	enum class STATE {
		NONE,
		WAIT,
		WALK,
		DASH,
		JUMP,
	};
	STATE _state; // �v���C���[�̏��
};
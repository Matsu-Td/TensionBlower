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

	int _attachIndex;
	float _totalTime;
	float _playTime;
	float _mvSpd;
	bool _isCharging;
	bool _hit;     // �f�o�b�O�̂�


	float _inVel;      // �����x
	float  _jumpTime;  // �W�����v���Ԑ���
	bool _isCanJump;   // �W�����v��(true:��, false:�s��)

	bool _isShortDash;      // �Z�����_�b�V������(true:�_�b�V����)
	int _dashCnt;      // �Z�����_�b�V���J�E���g

	// �v���C���[���(���[�V����)�Ǘ�
	enum class STATE {  
		NONE,
		WAIT,            // �ҋ@
		WALK,            // �ʏ�ړ�
		DASH,            // �_�b�V���ړ�
		JUMP,            // �W�����v
		L_SIDE_DASH,     // �������_�b�V���ړ�
		R_SIDE_DASH,     // �E�����_�b�V���ړ�
		BACK_DASH,       // ������_�b�V���ړ�
	};
	STATE _state; // �v���C���[�̏��

	PlayerBullet _bullet;
};

/*
// �W�����v1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/
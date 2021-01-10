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

	void ShortDash();
	void NormDash();
	void JumpAction();
	void Charging();
	void MortionSwitch();

	/**
	* �J�������b�N���̈ړ��A�_�b�V�����[�V�����ؑ֏����^
	* ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
	* @param length  := sqrt(lx * lx + ly * ly) ���A�i���O�X�e�B�b�N�̓��͒l
	*/
	void LeftAnalogDeg(float length);

	static Player* GetInstance() { return _pInstance; }
	VECTOR GetPos() const { return _vPos; }
	VECTOR GetDir() const { return _vDir; }
	int GetStatusAttack() const { return _status.nowAtck; }

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
	float _bsAngle;
	int _lfAnalogDeg;
	bool _isDash;

	float  _jumpTime;    // �W�����v���Ԑ���
	bool _isCanJump;     // �W�����v��(true:��, false:�s��)

	bool _isShortDash;   // �Z�����_�b�V������(true:�_�b�V����)
	int _dashCnt;        // �Z�����_�b�V���J�E���g

	// �v���C���[���(���[�V����)�Ǘ�
	enum class STATE {
		NONE,
		WAIT,            // �ҋ@
		WALK,            // �ʏ�ړ�
		JUMP,            // �W�����v
		LEFT_MOVE,       // �����ړ�(�J�������b�N���̂�)
		RIGHT_MOVE,      // �E���ړ�(�J�������b�N���̂�)
		BACK_MOVE,       // ����ړ�(�J�������b�N���̂�)
		FOR_DASH,        // �O���_�b�V���ړ�
		LEFT_DASH,       // �����_�b�V���ړ�(�J�������b�N���̂�)
		RIGHT_DASH,      // �E���_�b�V���ړ�(�J�������b�N���̂�)
		BACK_DASH,       // ����_�b�V���ړ�(�J�������b�N���̂�)
		WEAK_ATCK1,      // ��ߐڍU��1
		WEAK_ATCK2,      // ��ߐڍU��2
		WEAK_ATCK3,      // ��ߐڍU��3
		WEAK_ATCK4,      // ��ߐڍU��4
		STRG_ATCK1,      // ���ߐڍU��1
		STRG_ATCK2,      // ���ߐڍU��2
		STRG_ATCK3,      // ���ߐڍU��3
		STRG_ATCK4,      // ���ߐڍU��4
		SHOT_ATCK,       // �ˌ��U��
	};
	STATE _state; // �v���C���[�̏��

	PlayerBullet _bullet;

	static constexpr float NOR_MV_SPD = 0.8f;
	static constexpr float DASH_MV_SPD = 1.2f;
	static constexpr float CHARGE_MV_SPD = 0.4f;

	static constexpr int MAX_HP = 1000;
	static constexpr int MAX_ENERGY = 6000;

	struct STATUS {
		int hitpoint;
		int energy;
		int nowAtck;
		int wkAtck[4];
		int stAtck[4];
		int shooting;
	};
	STATUS _status;
};

/*
// �W�����v1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/
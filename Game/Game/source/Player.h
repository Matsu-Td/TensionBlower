#pragma once
#include "appframe.h"
#include "PlayerBullet.h"
#include "BulletServer.h"
#define  CHARA_DATA (modeGame->_charaData)

class Player : public ObjectBase
{
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	void ShortDash();
	void NormDash();
	void JumpAction();
	void Charging();
	void MortionSwitch();
	void AttackAction();
	void SetAttackDamage();
	MATRIX MV1GetFrameRotateMatrix(int MHandle, int FrameIndex, double Xaxis, double Yaxis, double Zaxis, double modelScale);


	/**
	* �J�������b�N���̈ړ��A�_�b�V�����[�V�����ؑ֏����^
	* ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
	* @param length  := sqrt(lx * lx + ly * ly) ���A�i���O�X�e�B�b�N�̓��͒l
	*/
	void LeftAnalogDeg(float length);

	static Player* GetInstance() { return _pInstance; }

	int GetEnergy() { return _energy; }
	int GetNowDmgHP() const { return _nowDmgHP; }
	int GetNowDmgSld() const { return _nowDmgSld; }
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.f;  // �n���Y���W

private:
	// �X�e�[�^�X�֘A
	int _hitpoint;       // �q�b�g�|�C���g�l
	int _energy;         // �G�l���M�[�l
	int _nowDmgHP;        // ���݂̋ߐڍU���̎��(�{�X�ւ̃_���[�W�p)
	int _nowDmgSld;
	int _nowDmgNorm;
	int _wkAtck[4];
	int _stAtck[4];
	int _bulletNum;      // �e�̎c�e��

	// �W�����v�֘A
	bool _isCanJump;     // �W�����v��(true:��, false:�s��)
	float  _jumpTime;    // �W�����v���Ԑ���

	// �_�b�V���֘A
	bool _isDash;        // �_�b�V���J�n(�S���)
	bool _isShortDash;   // �Z�����_�b�V������(true:�_�b�V����)
	bool _isCanLongDash; // �������_�b�V����(true:�\, false:�s��)
	int _shortDashTime;  // �Z�����_�b�V���ړ�����

	// �ˌ��֘A
	bool _canShotFlag;   // �ˌ���(true:�\, false:�s��)
	bool _shotZeroFlag;  // ���e���[���t���O(true:���e���u0�v���, false:���e���u1�v�ȏ゠����)
	int _shotInterval;   // �e�̔��ˊԊu
	int _reloadTime;     // �����[�h�J�n�܂ł̎���
	bool _shotFlag;      // �ˌ�����

	// �G�l���M�[���ߍs���֘A
	bool _isCharging;    // ���ߒ���(true:���ߒ�, false:���ߖ����{)
	bool _swCharge;      // �f�o�b�O�p(�G�l���M�[����ON/OFF�ؑ�)
	bool _atChargeFlag;  // �G�l���M�[�����񕜊J�n�t���O
	int _atChargeCnt;    // �G�l���M�[�����񕜊J�n�C���^�[�o��

	// �ߐڍU���֘A
	bool _attackFlag;      // �U�������t���O(�U��������)
	int _attackCnt;        // �U���J�ځA�I���J�E���g(�U�����[�V�������Đ����Ԃ���)
	int _attackReloadTime; // �ߐڍU���p�����[�h����(�����[�h���͋ߐڍU���s��)
	int _receptionTime;    // ���̋ߐڍU���J�ڎ�t����
	int _canHitFlag;       // �ߐڍU�������蔻���(true:�\, false:�s��)
	std::unordered_map<std::string, int> _attackTotalTime;  // �e�U�����[�V�����̑��Đ����Ԃ��i�[����

	// ���̑�
	bool _nearPosFlag;   // �{�X�̋߂��ɂ���Ƃ�
	float _bsAngle;      // �{�X�̈ʒu�A�p�x
	int _lfAnalogDeg;    // ���A�i���O�X�e�B�b�N�̓|��������(�p�x)
	int _gameOverCnt;    // �v���C���[���S����Q�[���I�[�o�[�܂ł̎���
	bool _gameOverFlag;
	bool _camStateMLS;   // �}���`���b�N�I���V�X�e����������

	// �v���C���[���(���[�V����)�Ǘ�
	enum class STATE {
		NONE,            // ����
		WAIT,            // �ҋ@
		WALK,            // �ʏ�ړ�
		FOR_DASH,        // �O���_�b�V���ړ�
		JUMP,            // �W�����v
		LEFT_MOVE,       // �����ړ�(�J�������b�N���̂�)
		RIGHT_MOVE,      // �E���ړ�(�J�������b�N���̂�)
		BACK_MOVE,       // ����ړ�(�J�������b�N���̂�)
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

	void EnergyManager(STATE oldState);

	static constexpr float GRAVITY = 0.9f;       // �d��
	static constexpr int SHORT_DASH_CNT = 10;    // �Z�����_�b�V������
	static constexpr int MAX_BULLET = 100;       // �ő呕�e��
	static constexpr int AT_CHARGE_CNT = 120;    // �����񕜊J�n�J�E���g
	static constexpr int RECEPTION_TIME = 30;    // ���ߐڍU����t����
	static constexpr int RELOAD_TIME = 90;  // �ߐځE�ˌ��U�������[�h����

	// �f�o�b�O�p
	float _len;          // �f�o�b�O�p�i�v���C���[�ƃ{�X�̋����j
};

/*
// �W�����v1
float acc = 0.05f;
_inVel -= acc;
_vPos.y += _inVel;
*/

//	static constexpr float NOR_MV_SPD = 0.8f;    // �ʏ푬�x
//	static constexpr float DASH_MV_SPD = 1.2f;   // �_�b�V�����x
//	static constexpr float CHARGE_MV_SPD = 0.2f; // ���ߍs�����̑��x
//	static constexpr int MAX_HP = 1000;          // �ő�q�b�g�|�C���g��
//	static constexpr int MAX_ENERGY = 6000;      // �ő�G�l���M�[��
//	static constexpr int JUMP_ENERGY = 1200;     // �W�����v�̃G�l���M�[�����
//	static constexpr int DASH_ENERGY = 600;      // �Z�����_�b�V�����̃G�l���M�[�����
//	static constexpr int AT_CHARGE = 2;          // 1f������G�l���M�[�����񕜗�
#pragma once

/**
 * @file  Player.h
 * @brief �v���C���[�֘A����
 *
 * @date 2021-02-08
 */

#include "appframe.h"
#include "PlayerBullet.h"
#include "BulletServer.h"
#define  CHARA_DATA (modeGame->_charaData)

class PlayerAttack;

class Player : public ObjectBase{
	friend PlayerAttack;
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	void ShortDash();
	void NormDash();
	void Charge();

	/**
	 * ����G�l���M�[����
	 * @param costEnergy ����G�l���M�[��
	 */
	void CostEnergy(float costEnergy);

	/**
     * �����蔻��
     */
	void Collision();

	/**
	 * �W�����v����
	 */
	void JumpAction();

	/**
     * �ˌ��U�� :�Q�[���p�b�hRT�Ŏˌ�
     * @param rt �Q�[���p�b�h�uRT�v���͒l
     */
	void ShotAttack(float rt);

	/**
	* �J�������b�N���̈ړ��A�_�b�V�����[�V�����ؑ֏����^
	* ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
	* @param length  := sqrt(lx * lx + ly * ly) ���A�i���O�X�e�B�b�N�̓��͒l
	*/
	void LeftAnalogDeg(float length);

	/**
	 * �G�l���M�[�ʎ擾
	 * @return �v���C���[�̌��݂̃G�l���M�[�ʂ��擾
	 */
	int GetEnergy() { return _energy; }

	/**
     * �ߐڍU���F�V�[���h��Ԃ̃{�X��HP�ɗ^����_���[�W�ʎ擾
     * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
     */
	int GetNowDmgHP()   const { return _nowDmgHP; }

	/**
	 * �ߐڍU���F�V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgSld()  const { return _nowDmgSld; }

	/**
	 * �ߐڍU���F�ʏ��Ԃ̃{�X��HP�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	/**
	 * �v���C���[�C���X�^���X�A�N�Z�X�p
	 * @return _pInstance �v���C���[�N���X�|�C���^
	 */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.0f;  // �n���Y���W

protected:


	// �X�e�[�^�X�֘A
	int _hitpoint;       // �q�b�g�|�C���g�l
	int _energy;         // �G�l���M�[�l
	int _nowDmgHP;       // ���݂̋ߐڍU���̎��(�{�X�ւ̃_���[�W�p)
	int _nowDmgSld;      // ���݂̋ߐڍU���̎��(�{�X�ւ̃_���[�W�p)
	int _nowDmgNorm;     // ���݂̋ߐڍU���̎��(�{�X�ւ̃_���[�W�p)
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
	bool _isCharging;    // �G�l���M�[���ߒ���(true:���ߒ�, false:���ߖ����{)
	bool _atChargeFlag;  // �G�l���M�[�����񕜊J�n�t���O
	int _atChargeCnt;    // �G�l���M�[�����񕜊J�n�C���^�[�o��

	// �ߐڍU���֘A
	bool _attackFlag;      // �U�������t���O(�U��������)
	int _attackCnt;        // �U���J�ځA�I���J�E���g(�U�����[�V�������Đ����Ԃ���)
	int _attackReloadTime; // �ߐڍU���p�����[�h����(�����[�h���͋ߐڍU���s��)
	int _receptionTime;    // ���̋ߐڍU���J�ڎ�t����
	int _canHitFlag;       // �ߐڍU�������蔻���(true:�\, false:�s��)

	std::unordered_map<std::string, int> _attackTotalTime;  // �e�U�����[�V�����̑��Đ����Ԃ��i�[����

	static constexpr int ATTACK_NUM = 8;  // �ߐڍU���̎�ނ̐�
	std::string AttackName[ATTACK_NUM] =  // �e�ߐڍU���̖��O���i�[
	{ "weak_atck1" ,"weak_atck2" ,"weak_atck3" ,"weak_atck4", 
	  "strg_atck1", "strg_atck2", "strg_atck3", "strg_atck4" };

	// ���̑�
	bool _nearPosFlag;   // �{�X�̋߂��ɂ��邩(true:�{�X�̋߂��ɂ���)
	float _bsAngle;      // �{�X�̈ʒu�A�p�x
	int _lfAnalogDeg;    // ���A�i���O�X�e�B�b�N�̓|��������(�p�x)
	int _gameOverCnt;    // �v���C���[���S����Q�[���I�[�o�[�܂ł̎���
	bool _gameOverFlag;  // �Q�[���I�[�o�[�t���O
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

	/**
	 * �G�l���M�[�Ǘ�
	 * @param oldState �����O�̃v���C���[�̏��
	 */
	void EnergyManager(STATE oldState);

	/**
	 * ���f�����[�V�����ؑ�
	 * @param oldState �����O�̃v���C���[�̏��
	 */
	void MortionSwitch(STATE oldState);

	static constexpr float GRAVITY       = 0.9f; // �d�͉����x�l
	static constexpr int SHORT_DASH_CNT  = 10;   // �Z�����_�b�V������
	static constexpr int MAX_BULLET      = 100;  // �ő呕�e��
	static constexpr int AUTO_CHARGE_CNT = 120;  // �����񕜊J�n�J�E���g
	static constexpr int RELOAD_TIME     = 90;   // �ߐځE�ˌ��U�������[�h����

	static constexpr int ANALOG_REG_FOR   = 120; // ���A�i���O�X�e�B�b�N��|���O��������̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)
	static constexpr int ANALOG_REG_OTHER = 45;  // ���A�i���O�X�e�B�b�N��|���O�����ȊO�̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)

	PlayerAttack* _attack;

	// �f�o�b�O�p
	float _len;          // �f�o�b�O�p�i�v���C���[�ƃ{�X�̋����j
	bool _swCharge;      // �f�o�b�O�p(�G�l���M�[����ON/OFF�ؑ�)
};

#include "PlayerAttack.h"
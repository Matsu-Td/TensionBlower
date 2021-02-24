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

// �v���C���[�N���X�Ɋ֌W����N���X�̐錾
class PlayerAttack;
class PlayerMotion;
class PlayerEnergy;
class PlayerDash;
class PlayerShoot;
class PlayerJump;

class Player : public ObjectBase{
	friend PlayerAttack;
	friend PlayerMotion;
	friend PlayerEnergy;
	friend PlayerDash;
	friend PlayerShoot;
	friend PlayerJump;
public:
	Player();
	~Player();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	void Initialize();
	void Process();
	void Render();

	/**
     * �����蔻��
     */
	void Collision();

	/**
	 * HP�l�擾
	 * @return �v���C���[�̌��݂�HP�l���擾
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * �G�l���M�[�ʎ擾
	 * @return �v���C���[�̌��݂̃G�l���M�[�ʂ��擾
	 */
	int GetEnergy() const { return _energy; }

	/**
	 * �e�̎c�e��
	 * @return �v���C���[�̌��݂̎c�e�����擾
	 */
	int GetBulletNum() const { return _bulletNum; }

	/**
     * �ߐڍU���F�V�[���h��Ԃ̃{�X��HP�ɗ^����_���[�W�ʎ擾
     * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
     */
	int GetNowDmgHP() const { return _nowDmgHP; }

	/**
	 * �ߐڍU���F�V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgSld() const { return _nowDmgSld; }

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
	// �X�e�[�^�X
	int _hitpoint;       // �q�b�g�|�C���g�l
	int _energy;         // �G�l���M�[�l

	// �W�����v�p
	float _jumpTime;     // �W�����v���Ԑ���
	bool  _canJump;      // �W�����v��(true:��, false:�s��)

	// �_�b�V���p
	int  _shortDashTime; // �Z�����_�b�V���ړ�����
	bool _isDash;        // �_�b�V���J�n(�S���)
	bool _isShortDash;   // �Z�����_�b�V������(true:�_�b�V����)
	bool _canLongDash;   // �������_�b�V����(true:�\, false:�s��)

	// �ˌ��p
	int  _shotInterval;  // �e�̔��ˊԊu
	int  _reloadTime;    // �����[�h�J�n�܂ł̎���
	int  _bulletNum;     // �e�̎c�e��
	bool _canShot;       // �ˌ���(true:�\, false:�s��)
	bool _isZeroShot;    // ���e���[���t���O(true:���e���u0�v���, false:���e���u1�v�ȏ゠����)
	bool _isShooting;    // �ˌ�����
	
	// �G�l���M�[���ߗp
	int  _autoChargeCnt; // �G�l���M�[�����񕜊J�n�C���^�[�o��
	bool _isCharging;    // �G�l���M�[���ߒ���(true:���ߒ�, false:���ߖ����{)
	bool _canAutoCharge; // �G�l���M�[�����񕜊J�n�t���O

	// �ߐڍU���p
	int  _attackCnt;        // �U���J�ځA�I���J�E���g(�U�����[�V�������Đ����Ԃ���)
	int  _attackReloadTime; // �ߐڍU���p�����[�h����(�����[�h���͋ߐڍU���s��)
	int  _receptionTime;    // ���̋ߐڍU���J�ڎ�t����
	int  _canHitFlag;       // �ߐڍU�������蔻���(true:�\, false:�s��)
	int  _nowDmgHP;         // �������ߐڍU����HP�֗^����_���[�W��(�V�[���h�L)
	int  _nowDmgSld;        // �������ߐڍU���̃V�[���h�֗^����_���[�W��
	int  _nowDmgNorm;       // �������ߐڍU����HP�֗^����_���[�W��(�V�[���h��)
	bool _isAttack;         // �U�������t���O(�U��������)

	std::unordered_map<std::string, int> _attackTotalTime;  // �e�U�����[�V�����̑��Đ����Ԃ��i�[����

	static constexpr int ATTACK_NUM = 8;  // �ߐڍU���̎�ނ̐�
	std::string _attackString[ATTACK_NUM] =  // �e�ߐڍU���̖��O���i�[
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l", 
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	const TCHAR* _attackTchar[ATTACK_NUM] =  // �e�ߐڍU���̖��O���i�[
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l",
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	// �Q�[���I�[�o�[�p
	int  _gameOverCnt;   // �v���C���[���S����Q�[���I�[�o�[�܂ł̎���
	bool _isGameOver;   // �Q�[���I�[�o�[�t���O

	// ���̑�
	int   _lfAnalogDeg;   // ���A�i���O�X�e�B�b�N�̓|��������(�p�x)
	float _bsAngle;     // �{�X�̈ʒu�A�p�x
	bool  _isNearBoss;   // �{�X�̋߂��ɂ��邩(true:�{�X�̋߂��ɂ���)	
	bool  _camStateMLS;  // �}���`���b�N�I���V�X�e����������


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
		DEAD,            // ���S
	};
	STATE _state; // �v���C���[�̏��

	static constexpr float GRAVITY       = 0.9f; // �d�͉����x�l
	static constexpr int MAX_BULLET      = 100;  // �ő呕�e��
	static constexpr int RELOAD_TIME     = 90;   // �ߐځE�ˌ��U�������[�h����
	static constexpr int AUTO_CHARGE_CNT = 120;  // �����񕜊J�n�J�E���g
	static constexpr float ANALOG_MIN    = 0.3f; // �A�i���O�X�e�B�b�N���͔����̍ŏ��l

	PlayerAttack* _attackCall;  // �����Ăяo���F�ߐڍU������
	PlayerMotion* _motionCall;  // �����Ăяo���F���[�V�����ؑ֏���
	PlayerEnergy* _energyCall;  // �����Ăяo���F�G�l���M�[�Ǘ�����
	PlayerDash*   _dashCall;    // �����Ăяo���F�_�b�V������
	PlayerShoot*  _shootCall;   // �����Ăяo���F�ˌ��U������
	PlayerJump*   _JumpCall;    // �����Ăяo���F�W�����v����

	// �f�o�b�O�p
	float _len;          // �f�o�b�O�p�i�v���C���[�ƃ{�X�̋����j
	bool _swCharge;      // �f�o�b�O�p(�G�l���M�[����ON/OFF�ؑ�)
};

#include "PlayerAttack.h"
#include "PlayerMotion.h"
#include "PlayerEnergy.h"
#include "PlayerDash.h"
#include "PlayerShoot.h"
#include "PlayerJump.h"
/**
 * @file   Player.h
 * @brief  �v���C���[�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"
#include "../Boss/BossDamage.h"

// �v���C���[�N���X�Ɋ֌W����N���X�̐錾
class PlayerAttack;
class PlayerMotion;
class PlayerEnergy;
class PlayerDash;
class PlayerJump;

/**
 * �v���C���[�N���X
 */
class Player : public ObjectBase{
	// ���L�t�@�C�������private�ւ̃A�N�Z�X���\�ɂ���
	friend PlayerAttack;
	friend PlayerMotion;
	friend PlayerEnergy;
	friend PlayerDash;
	friend PlayerJump;
public:
	Player();
	~Player();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	/**
	 * ������
	 */
	void Initialize() override;

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �t���[�������F�`��
	 */
	void Render() override;

	/**
	 * �ړ�����
	 */
	void Move();

	/**
	 * �d�͏���
	 */
	void Gravity();

	/**
	 * �G�l���M�[���ߏ���
	 */
	void Charge();

	/**
	 * �}���`���b�N�I���V�X�e���p�Ə��ǉ�
	 */
	void ReticleGeneration();

	/**
	 * �{�X�Ƃ̋������m�F(�����񕜗p)
	 */
	void CheckDistanceToBoss();

	/**
	 * �����蔻��F�X�e�[�W
	 */
	void CollisionToStage();

	/**
	 * �����蔻��F�{�X�̒e
	 */
	void CollisionToBossBullet();

	/**
	 * �����蔻��F�{�X
	 */
	void CollisionToBoss();

	/**
	 * �����蔻��F�{�X�̃��[�U�[�U��
	 */
	void CollisionToLaser();

	/**
	 * �Q�[���I�[�o�[����
	 */
	void GameOver();

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
	 * �{���̔����_���[�W
	 */
	void ExplosionDamage();

	/**
	 * �v���C���[�C���X�^���X�A�N�Z�X�p
	 * @return _pInstance �v���C���[�N���X�|�C���^
	 */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	static constexpr float GROUND_Y = 0.0f;  // �n���Y���W

	int  _canHitFlag;       // �ߐڍU�������蔻���(true:�\, false:�s��)
private:
	float _analogLength;
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
	
	// �G�l���M�[���ߗp
	int  _autoChargeCnt; // �G�l���M�[�����񕜊J�n�C���^�[�o��
	bool _isCharging;    // �G�l���M�[���ߒ���(true:���ߒ�, false:���ߖ����{)
	bool _canAutoCharge; // �G�l���M�[�����񕜊J�n�t���O

	// �ߐڍU���p
	int  _attackCnt;        // �U���J�ځA�I���J�E���g(�U�����[�V�������Đ����Ԃ���)
	int  _attackReloadTime; // �ߐڍU���p�����[�h����(�����[�h���͋ߐڍU���s��)
	int  _receptionTime;    // ���̋ߐڍU���J�ڎ�t����
	int  _nowDmgHP;         // �������ߐڍU����HP�֗^����_���[�W��(�V�[���h�L)
	int  _nowDmgSld;        // �������ߐڍU���̃V�[���h�֗^����_���[�W��
	int  _nowDmgNorm;       // �������ߐڍU����HP�֗^����_���[�W��(�V�[���h��)
	int  _hitStart;
	int  _hitEnd;
	bool _isAttack;         // �U�������t���O(�U��������)

	std::unordered_map<std::string, int> _attackTotalTime;  // �e�U�����[�V�����̑��Đ����Ԃ��i�[����

	static const int ATTACK_NUM = 8;         // �ߐڍU���̎�ނ̐�
	std::string _attackString[ATTACK_NUM] =      // �e�ߐڍU���̖��O���i�[
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l", 
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	const TCHAR* _attackTchar[ATTACK_NUM] =      // �e�ߐڍU���̖��O���i�[
	{ "slash_l" ,"slash_l" ,"slash_l" ,"slash_l",
	  "slash_h", "slash_h", "slash_h", "slash_h" };

	// �Q�[���I�[�o�[�p
	int  _gameOverCnt;   // �v���C���[���S����Q�[���I�[�o�[�܂ł̎���
	bool _isGameOver;    // �Q�[���I�[�o�[�t���O

	// ���̑�
	int   _lfAnalogDeg;  // ���A�i���O�X�e�B�b�N�̓|��������(�p�x)
	float _bsAngle;      // �{�X�̈ʒu�A�p�x
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
		DEAD,            // ���S
	};
	STATE _state; // �v���C���[�̏��

	static constexpr float GRAVITY       = 0.9f; // �d�͉����x�l
	static constexpr int AUTO_CHARGE_CNT = 120;  // �����񕜊J�n�J�E���g
	const int RELOAD_TIME     = 90;   // �ߐځE�ˌ��U�������[�h����
	const float ANALOG_MIN    = 0.3f; // �A�i���O�X�e�B�b�N���͔����̍ŏ��l

	PlayerAttack* _attackCall;  // �����Ăяo���F�ߐڍU������
	PlayerMotion* _motionCall;  // �����Ăяo���F���[�V�����ؑ֏���
	PlayerEnergy* _energyCall;  // �����Ăяo���F�G�l���M�[�Ǘ�����
	PlayerDash*   _dashCall;    // �����Ăяo���F�_�b�V������
	PlayerJump*   _JumpCall;    // �����Ăяo���F�W�����v����

	std::unique_ptr<BossDamage> _bossDamageCall;  	// �{�X�ւ̃_���[�W�����Ăяo��
};

#include "PlayerAttack.h"
#include "PlayerMotion.h"
#include "PlayerEnergy.h"
#include "PlayerDash.h"
#include "PlayerJump.h"
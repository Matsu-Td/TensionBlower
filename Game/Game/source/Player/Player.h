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

/**
 * @brief �v���C���[�N���X
 */
class Player : public ObjectBase{
public:
	Player();
	virtual ~Player();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::PLAYER; }

	/**
	 * @brief ������
	 */
	void Initialize() override;

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render() override;

	/**
     * @brief  HP�l�擾
     * @return �v���C���[�̌��݂�HP�l���擾
     */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief  �G�l���M�[�ʎ擾
	 * @return �v���C���[�̌��݂̃G�l���M�[�ʂ��擾
	 */
	int GetEnergy() const { return _energy; }

	/**
	 * @brief  �ߐڍU���F�V�[���h��Ԃ̃{�X��HP�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgHP() const { return _nowDmgHP; }

	/**
	 * @brief  �ߐڍU���F�V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgSld() const { return _nowDmgSld; }

	/**
	 * @brief  �ߐڍU���F�ʏ��Ԃ̃{�X��HP�ɗ^����_���[�W�ʎ擾
	 * @return �v���C���[�̌��݂̋ߐڍU���_���[�W��
	 */
	int GetNowDmgNorm() const { return _nowDmgNorm; }

	/**
	 * @brief �{���̔����_���[�W
	 */
	void ExplosionDamage();

	/**
     * @brief  �v���C���[�C���X�^���X�A�N�Z�X�p
     * @return Player�̃C���X�^���X
     */
	static Player* GetInstance() { return _pInstance; }
	static Player* _pInstance;

	int _canHitFlag;  // �ߐڍU�������蔻���(true:�\, false:�s��)

private:
	/**
	 * @brief �ړ�����
	 */
	void Move();

	/**
	 * @brief �d�͏���
	 */
	void Gravity();

	/**
	 * @brief �G�l���M�[���ߏ���
	 */
	void Charge();

	/**
	 * @brief �}���`���b�N�I���V�X�e���p�Ə��ǉ�
	 */
	void ReticleGeneration();

	/**
	 * @brief �{�X�Ƃ̋������m�F(�����񕜗p)
	 */
	void CheckDistanceToBoss();

	/**
     * @brief �e�퓖���蔻�菈�����s
     */
	void AllCollision();

	/**
	 * @brief �����蔻��F�X�e�[�W
	 */
	void CollisionToStage();

	/**
	 * @brief �����蔻��F�{�X�̒e
	 */
	void CollisionToBossBullet();

	/**
	 * @brief �����蔻��F�{�X
	 */
	void CollisionToBoss();

	/**
	 * @brief �����蔻��F�{�X�̃��[�U�[�U��
	 */
	void CollisionToLaser();

	/**
	 * @brief ���S�������Q�[���I�[�o�[�ֈڍs
	 */
	void Death();

	/**
	 * ���[�V�����̖��O�Ŏw�肵�����f���̃��[�V�������A�^�b�`����
	 * @param  animName ���[�V������
	 * @return ���[�V�����ԍ�
	 */
	int AttachAnim(const TCHAR* animName) const;

	/**
	 * @brief ���[�V�����ؑ֏���
	 */
	void MotionSwitching();

	/**
	 * @brief �W�����v����
	 */
	void Jump();

	/**
	 * @brief �G�l���M�[�����
	 * @param costEnergy �����G�l���M�[��
	 */
	void CostEnergy(int costEnergy);

	/**
	 * @brief �G�l���M�[�̉񕜁A�����
	 */
	void EnergyManager();

	/**
	 * @brief �ړ��A�_�b�V�����[�V�����ؑ֏���
	 * @brief ���A�i���O�X�e�B�b�N�̓|�����p�x�ɂ���ăL�����̏�ԁA���[�V������J��
	 */
	void LeftAnalogDeg();

	/**
	 * @brief �_�b�V������
	 */
	void Dash();

	/**
	 * @brief �ߐڍU���̃_���[�W�ʂ��ߐڍU���̎�ނɂ���Đؑ�
	 * @param player  �v���C���[�N���X�I�u�W�F�N�g�̃|�C���^
	 */
	void SwitchAttackDamage();

	/**
	 * @brief ���ݔ������̋ߐڍU���_���[�W�ʂ�ݒ肷��
	 * @param dmgHP   �V�[���h��Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
	 * @param dmgSld  �V�[���h��Ԃ̃{�X�̃V�[���h�ɗ^����_���[�W��
	 * @param dmgNorm �V�[���h���Ȃ���Ԃ̃{�X�̃q�b�g�|�C���g�ɗ^����_���[�W��
	 */
	void SetAttackDamage(int dmgHP, int dmgSld, int dmgNorm);

	/**
	 * @brief �e�ߐڍU���ւ̃L�[���͏���
	 */
	void AttackAction();

	/**
	 * @brief �ߐڍU������(����̂�)
	 */
	void FirstAttack();

	/**
	 * @brief �ߐڍU������(2���ڈȍ~)
	 */
	void SecondAttack();

	/**
	 * @brief �U���������̐��f�[�^���Đ�����
	 * @param voiceName �Đ����鐺�f�[�^�̖��O
	 */
	void PlayAttackVoice(std::string voiceName);

	/**
	 * @brief ��ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
	 */
	void SetWeakHitTime();

	/**
	 * @brief ���ߐڍU���̃q�b�g���莞�Ԃ�ݒ肷��
	 */
	void SetStrongHitTime();

private:
	float _analogLength; // ���A�i���O�X�e�B�b�N�̓��́A�|�����傫��

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
	int  _hitStartCnt;      // �ߐڍU���̓����蔻�蔭���J�n�J�E���g
	int  _hitEndCnt;        // �ߐڍU���̓����蔻�蔭���I���J�E���g
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

	/**
	 * @brief �v���C���[��ԑJ�ڗp
	 */
	enum class STATE {
		NONE,          // ����
		WAIT,          // �ҋ@
		WALK,          // �ʏ�ړ�
		FOR_DASH,      // �O���_�b�V���ړ�
		JUMP,          // �W�����v
		LEFT_MOVE,     // �����ړ�
		RIGHT_MOVE,    // �E���ړ�
		BACK_MOVE,     // ����ړ�
		LEFT_DASH,     // �����_�b�V���ړ�
		RIGHT_DASH,    // �E���_�b�V���ړ�
		BACK_DASH,     // ����_�b�V���ړ�
		WEAK_ATCK1,    // ��ߐڍU��1
		WEAK_ATCK2,    // ��ߐڍU��2
		WEAK_ATCK3,    // ��ߐڍU��3
		WEAK_ATCK4,    // ��ߐڍU��4
		STRG_ATCK1,    // ���ߐڍU��1
		STRG_ATCK2,    // ���ߐڍU��2
		STRG_ATCK3,    // ���ߐڍU��3
		STRG_ATCK4,    // ���ߐڍU��4
		DEATH,         // ���S
	};
	STATE _state;    // �v���C���[�̏��
	STATE _oldState; // �����O�̃v���C���[�̏��
	
	// �萔
	const float GROUND_Y      = 0.0f;  // �n���Y���W
	const float GRAVITY       = 0.9f;  // �d�͉����x�l
	const float ANALOG_MIN    = 0.3f;  // �A�i���O�X�e�B�b�N���͔����̍ŏ��l
	const float IN_VEL        = 5.0f;         // ����
	const float MULT_HALF     = 0.5f;      // 1/2��Z
	const float JUMP_CNT      = 0.2f;       // �W�����v����

	const int SHORT_DASH_CNT     = 10;     // �Z�����_�b�V���ړ�����
	const int AUTO_CHARGE_CNT    = 120;   // �G�l���M�[�����񕜊J�n�J�E���g
	const int RELOAD_TIME        = 90;    // �ߐځE�ˌ��U�������[�h����
	const int ANALOG_REG_FOR     = 120;    // ���A�i���O�X�e�B�b�N��|���O��������̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)
	const int ANALOG_REG_OTHER   = 45;   // ���A�i���O�X�e�B�b�N��|���O�����ȊO�̊p�x�͈�(�^�[�Q�b�g���b�N���̂ݎg�p)
	const int RECEPTION_TIME     = 30;     // ���ߐڍU����t����
	const int ATTACK_RELOAD_TIME = 90; // �ߐځE�ˌ��U�������[�h����

	std::unique_ptr<BossDamage> _bossDamageCall;  	// �{�X�ւ̃_���[�W�����Ăяo��

	/**
	 * @brief ���ߐڍU���ւ̔h���֘A����
	 * @param attackEnergy �w�肳�ꂽ���ߐڍU���ł̏���G�l���M�[��
	 * @param nextState    �h�����鋭�ߐڍU���̎��
	 * @param attackName   �h�����鋭�ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
	 */
	void NextStrongAttack(int attackEnergy, STATE nextState, std::string attackName);

	/**
	 * @brief ��ߐڍU���ւ̔h���֘A����
	 * @param nextState    �h�������ߐڍU���̎��
	 * @param attackName   �h�������ߐڍU���̖��O(�U�����[�V�������ԃZ�b�g�p)
	 */
	void NextWeakAttack(STATE nextState, std::string attackName);
};
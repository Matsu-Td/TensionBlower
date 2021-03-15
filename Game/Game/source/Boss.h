/**
 * @file   Boss.h
 * @brief  �{�X�֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#define  CHARA_DATA (modeGame->_charaData)

class Boss : public ObjectBase{
public:
	Boss();
	~Boss();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

	void Initialize();
	void Process();
	void Render();

	/**
	 * @brief �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
     */
	void RepelDamage();

	/**
	 * @brief �v���C���[����󂯂��_���[�W�ʌv�Z
	 */
	void AttackDamage();

	/**
	 * @brief �q�b�g�|�C���g�ւ̔����_���[�W
	 */
	void ExplosionDamageHP();

	/**
	 * @brief �V�[���h�ւ̔����_���[�W
	 */
	void ExplosionDamageShield();

	/**
	 * @brief �t�F�[�Y�ύX����
	 */
	void FhaseChange();

	/**
	 * @brief �e���p�^�[���ؑ֏���
	 */
	void ShotPatternSwitch();

	/**
	 * @brief �_�E����ԏ���
	 */
	void StateDown();

	/**
	 * @brief �e���p�^�[��1&2
	 */
	void ShotPattern1and2();

	/**
	 * @brief �e���p�^�[��3
	 */
	void ShotPattern3();

	/**
	 * @brief �e���p�^�[��4-1
	 */
	void ShotPattern4_1();

	/**
	 * @brief �e���p�^�[��4-2
	 */
	void ShotPattern4_2();

	/**
     * @brief �e���p�^�[��5
     */
	void ShotPattern5();

	/**
     * @brief �e���p�^�[��6
     */
	void ShotPattern6();

	/**
	 * @brief �e���p�^�[��7
	 */
	void ShotPattern7();

	/**
	 * @brief ���[�U�[�U��1-1
	 */
	void LaserAttack1_1();

	/**
	 * @brief ���[�U�[�U��1-2
	 */
	void LaserAttack1_2();

	/**
	 * @brief ���[�U�[�U��2
	 */
	void LaserAttack2();

	/**
	 * @brief 6��ނ̐��f�[�^�������_���ŗ���
	 */
	void PlayAttackVoiceChange();

	/**
	 * @brief ���f�[�^�Đ�
	 * @param voiceName ���f�[�^�̖��O
	 */
	void PlayVoice(std::string voiceName);

	/**
	 * @brief �q�b�g�|�C���g�l�擾
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief �V�[���h�l�擾
	 */
	int GetShield() const { return _shield; }

	/**
	 * �t�F�[�Y���擾
	 */
	int GetPhase() const { return _phase; }

	/**
	 * @brief ���S����
	 */
	void Dead();

	static Boss* GetInstance() { return _pInstance; }

	static Boss* _pInstance;

	// �v���C���[�N���X�Ŏg�p
	int _bulletNum;      // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
	bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E������Ɓutrue�v

	// ���
	enum class STATE {
		NORMAL,  // �ʏ�
		DOWN,    // �_�E��
		RETURN,  // ���A
		DEAD,    // ���S�A�j��
	};
	STATE GetState() const { return _state; };

private:
	int _hitpoint;       // �q�b�g�|�C���g�l
	int _shield;         // �V�[���h�l
	int _downTime;       // �_�E������
	bool _stateDown;     // �_�E����Ԃ�(true:�_�E�����)

	int _shotCnt;        // �e�����˃^�C�~���O�J�E���g
	int _mlsCnt;         // �}���`���b�N�I���V�X�e���������̃J�E���g
	int _reverseCnt;     // �e����]���������]����J�E���g
	float _shotAngle;    // �e���̔��ˊp�x
	float _shotAngle1;   // �e���̔��ˊp�x
	float _setRotAngle;  // ���ˈ��p�x�Z�b�g
	float shotInterval;  // �e���̔��ˊԊu
	int _shotPattern;    // �e���p�^�[��3�탉���_���Őؑ�
	int _phase;          // �t�F�[�Y�FHP�c�ʂŕω�
	float _shotHeight;   // �e���𔭎˂��鍂��
	float _laserAngle;   // ���[�U�[�̔��ˊp�x

	int  _deadCnt;  // ���S�J�E���g
	bool _deadFlag; // ���S�t���O

	static constexpr int ATTACK_VOICE_NUM = 6;    // �U�����̐��f�[�^����
	std::string _attackNameNo[ATTACK_VOICE_NUM] =  // �U�����̐��f�[�^�̖��O���i�[
	{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };

	static constexpr float SHOT_DISTANCE = 10.0f;  // �e���𔭐�������ʒu(�{�X���S����̋���)
	static constexpr float ADD_POS_Y     = 9.0f;   // �����蔻��pY���W���Z�l
	static constexpr float ROT_SPD       = 0.01f;  // �{�X�̌�����]�p�p���x

	static constexpr int PATTERN_CHANGE_CNT = 240; // �e���p�^�[����ω�������J�E���g�ő�l
	static constexpr int SHOT_REVERSE_CNT = 90;    // �e����]������ω�������J�E���g�ő�l
	static constexpr int PHASE_ONE_HP   = 4000;    // �t�F�[�Y1�ֈڍs����c��HP��
	static constexpr int PHASE_TWO_HP   = 3000;    // �t�F�[�Y2�ֈڍs����c��HP��
	static constexpr int PHASE_THREE_HP = 2000;    // �t�F�[�Y3�ֈڍs����c��HP��
	static constexpr int PHASE_FOUR_HP  = 1000;    // �t�F�[�Y4�ֈڍs����c��HP��
	static constexpr int MIN_DOWN_TIME = 180;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)
	static constexpr int EXPLOSION_DMG_NORM = 2;   // ����HP�_���[�W�ʁF�ʏ펞(�V�[���h��)
	static constexpr int EXPLOSION_DMG_HP = 1;     // ����HP�_���[�W��(�V�[���h�L)
	static constexpr int EXPLOSION_DMG_SLD = 2;    // �����V�[���h�_���[�W��(�V�[���h�L)
	STATE _state;  // ���
};

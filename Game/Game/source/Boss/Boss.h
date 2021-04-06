/**
 * @file   Boss.h
 * @brief  �{�X�N���X
 * 
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * @brief �{�X�N���X
 */
class Boss : public ObjectBase{
public:
	Boss();
	~Boss();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

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
	 * @brief  �q�b�g�|�C���g�l�擾
	 * @return �q�b�g�|�C���g
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief  �V�[���h�l�擾
	 * @return �V�[���h�l
	 */
	int GetShield() const { return _shield; }

	/**
	 * @brief  �t�F�[�Y���擾
	 * @return ���݂̃t�F�[�Y
	 */
	int GetPhase() const { return _phase; }

	/**
�@�@ * @brief �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
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
	 * @brief Boss�C���X�^���X���擾����
	 */
	static Boss* GetInstance() { return _pInstance; }

	static Boss* _pInstance;

	// �v���C���[�N���X�Ŏg�p
	int _bulletNum;      // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
	bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E������Ɓutrue�v

	/**
	 * @brief ���
	 */
	enum class STATE {
		NORMAL,  // �ʏ�
		DOWN,    // �_�E��
		RETURN,  // ���A
	};
	STATE GetState() const { return _state; };

private:
	/**
     * ���[�V�����ؑ�
     * @param  oldState �����O�̏��
     */
	void MotionSwitch();

	/**
     * @brief ���S����
     */
	void Death();

	/**
     * @brief �e���p�^�[���ؑ֏���
     */
	void ShotPatternSwitch();
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
	 * @brief �t�F�[�Y�ύX����
	 */
	void FhaseChange();

	/**
	 * @brief �_�E����ԏ���
	 */
	void StateDown();

	/**
	 * @brief 6��ނ̐��f�[�^�������_���ōĐ�
	 */
	void PlayAttackVoiceChange();

	/**
	 * @brief ���f�[�^�Đ�
	 * @param voiceName ���f�[�^�̖��O
	 */
	void PlayVoice(std::string voiceName);

	/**
	 * @brief �{�X���ʕ�����]����
	 * @param rotSpdChenge ��]���x�ؑ֗p
	 */
	void DirectionalRotation(float rotSpdChange);

private:
	int  _hitpoint;      // �q�b�g�|�C���g�l
	int  _shield;        // �V�[���h�l
	int  _downTime;      // �_�E������
	bool _stateDown;     // �_�E����Ԃ�(true:�_�E�����)
	float _sinCnt;       // �㉺�^���p�T�C���g�J�E���g

	int   _shotCnt;      // �e�����˃^�C�~���O�J�E���g
	int   _mlsCnt;       // �}���`���b�N�I���V�X�e���������̃J�E���g
	int   _reverseCnt;   // �e����]���������]����J�E���g
	float _shotAngle;    // �e���̔��ˊp�x
	float _shotAngle1;   // �e���̔��ˊp�x
	float _setRotAngle;  // ���ˈ��p�x�Z�b�g
	int   _shotPattern;  // �e���p�^�[��3�탉���_���Őؑ�
	int   _phase;        // �t�F�[�Y�FHP�c�ʂŕω�
	float _shotHeight;   // �e���𔭎˂��鍂��
	float _laserAngle;   // ���[�U�[�̔��ˊp�x

	int  _deathCnt;  // ���S�J�E���g
	bool _deathFlag; // ���S�t���O

	static const int ATTACK_VOICE_NUM = 6;     // �U�����̐��f�[�^����
	std::string _attackNameNo[ATTACK_VOICE_NUM] =  // �U�����̐��f�[�^�̖��O���i�[
	{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };

	STATE _state;    // ���
	STATE _oldState; // �����O�̏��

	VECTOR _cross;   // �O��(�{�X�̌�����]�v�Z�p)

	// �萔
	const float ADD_POS_Y = 9.0f;   // �����蔻��pY���W���Z�l
	const float ROT_SPD = 0.01f;  // �{�X�̌�����]�p�p���x
	const int PHASE_ONE_HP = 4000;    // �t�F�[�Y1�ֈڍs����c��HP��
	const int PHASE_TWO_HP = 3000;    // �t�F�[�Y2�ֈڍs����c��HP��
	const int PHASE_THREE_HP = 2000;    // �t�F�[�Y3�ֈڍs����c��HP��
	const int PHASE_FOUR_HP = 1000;    // �t�F�[�Y4�ֈڍs����c��HP��
	const int MIN_DOWN_TIME = 180;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)
	const int PATTERN_CHANGE_CNT = 240; // �e���p�^�[����ω�������J�E���g�ő�l
	const int SHOT_REVERSE_CNT = 90;    // �e����]������ω�������J�E���g�ő�l
	const float SHOT_DISTANCE = 10.0f;  // �e���𔭐�������ʒu(�{�X���S����̋���)
	const int EXPLOSION_DMG_NORM = 2;   // ����HP�_���[�W�ʁF�ʏ펞(�V�[���h��)
	const int EXPLOSION_DMG_HP = 1;     // ����HP�_���[�W��(�V�[���h�L)
	const int EXPLOSION_DMG_SLD = 2;    // �����V�[���h�_���[�W��(�V�[���h�L)
};

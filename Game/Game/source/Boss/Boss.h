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

class ShotPattern;
class BossDamage;

/**
 * @brief �{�X�N���X
 */
class Boss : public ObjectBase{
	friend ShotPattern;
	friend BossDamage;
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
	 * @brief �t�F�[�Y�ύX����
	 */
	void FhaseChange();

	/**
	 * @brief �_�E����ԏ���
	 */
	void StateDown();

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
	 * @brief �{�X���ʕ�����]����
	 * @param rotSpdChenge ��]���x�ؑ֗p
	 */
	void DirectionalRotation(float rotSpdChenge);

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
	 * @brief ���S����
	 */
	void Dead();

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
		DEAD,    // ���S�A�j��
	};
	STATE GetState() const { return _state; };

	/**
	 * ���[�V�����ؑ�
	 * @param  oldState �����O�̏��
	 */
	void MotionSwitch(STATE oldState);

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

	int  _deadCnt;  // ���S�J�E���g
	bool _deadFlag; // ���S�t���O

	static const int ATTACK_VOICE_NUM = 6;     // �U�����̐��f�[�^����
	std::string _attackNameNo[ATTACK_VOICE_NUM] =  // �U�����̐��f�[�^�̖��O���i�[
	{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };

	const float ADD_POS_Y     = 9.0f;   // �����蔻��pY���W���Z�l
	const float ROT_SPD       = 0.01f;  // �{�X�̌�����]�p�p���x

	const int PHASE_ONE_HP   = 4000;    // �t�F�[�Y1�ֈڍs����c��HP��
	const int PHASE_TWO_HP   = 3000;    // �t�F�[�Y2�ֈڍs����c��HP��
	const int PHASE_THREE_HP = 2000;    // �t�F�[�Y3�ֈڍs����c��HP��
	const int PHASE_FOUR_HP  = 1000;    // �t�F�[�Y4�ֈڍs����c��HP��
	const int MIN_DOWN_TIME = 180;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)

	STATE _state;  // ���

	std::unique_ptr<ShotPattern> _patternCall; // �����Ăяo���F�e���p�^�[��
	std::unique_ptr<BossDamage>  _damageCall;  // �����Ăяo���F�_���[�W����

	VECTOR _cross;
};

#include "ShotPattern.h"
#include "BossDamage.h"

/**
 * @file   Boss.h
 * @brief  �{�X�֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"
#define  CHARA_DATA (modeGame->_charaData)

class ShotPattern;
class BossDamage;

class Boss : public ObjectBase{
	friend ShotPattern;
	friend BossDamage;
public:
	Boss();
	~Boss();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS; }

	/**
	 * @brief ������
	 */
	void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process();

	/**
	 * @brief �t���[�������F�`��
	 */
	void Render();

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
	 * @brief �q�b�g�|�C���g�l�擾
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * @brief �V�[���h�l�擾
	 */
	int GetShield() const { return _shield; }

	/**
	 * @brief �t�F�[�Y���擾
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
	int  _hitpoint;      // �q�b�g�|�C���g�l
	int  _shield;        // �V�[���h�l
	int  _downTime;      // �_�E������
	bool _stateDown;     // �_�E����Ԃ�(true:�_�E�����)

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

	static constexpr int ATTACK_VOICE_NUM = 6;     // �U�����̐��f�[�^����
	std::string _attackNameNo[ATTACK_VOICE_NUM] =  // �U�����̐��f�[�^�̖��O���i�[
	{ "attack1","attack1" ,"attack2" ,"attack4" ,"attack5" ,"attack6" };


	static constexpr float ADD_POS_Y     = 9.0f;   // �����蔻��pY���W���Z�l
	static constexpr float ROT_SPD       = 0.01f;  // �{�X�̌�����]�p�p���x

	static constexpr int PHASE_ONE_HP   = 4000;    // �t�F�[�Y1�ֈڍs����c��HP��
	static constexpr int PHASE_TWO_HP   = 3000;    // �t�F�[�Y2�ֈڍs����c��HP��
	static constexpr int PHASE_THREE_HP = 2000;    // �t�F�[�Y3�ֈڍs����c��HP��
	static constexpr int PHASE_FOUR_HP  = 1000;    // �t�F�[�Y4�ֈڍs����c��HP��
	static constexpr int MIN_DOWN_TIME = 180;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)

	STATE _state;  // ���

	std::unique_ptr<ShotPattern> _patternCall;
	std::unique_ptr<BossDamage> _damageCall;
};

#include "ShotPattern.h"
#include "BossDamage.h"

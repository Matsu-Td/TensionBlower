/**
 * @file   Boss.h
 * @brief  �{�X�֘A����
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "BossBullet.h"
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
	 * �v���C���[�ɒe���Ԃ��ꂽ�e�ɂ��_���[�W����
     */
	void Damage();

	/**
	 * �v���C���[����󂯂��_���[�W�ʌv�Z
	 */
	void AttackDamage();

	/**
	 * �t�F�[�Y�ύX����
	 */
	void FhaseChange();

	/**
	 * �e���p�^�[���ؑ֏���
	 */
	void ShotPatternSwitch();

	/**
	 * �_�E����ԏ���
	 */
	void StateDown();

	/**
	 * �e���p�^�[��1&2
	 */
	void ShotPattern1and2();

	/**
	 * �e���p�^�[��3
	 */
	void ShotPattern3();

	/**
	 * �e���p�^�[��4-1
	 */
	void ShotPattern4_1();

	/**
	 * �e���p�^�[��4-2
	 */
	void ShotPattern4_2();

	/**
     * �e���p�^�[��5
     */
	void ShotPattern5();

	/**
     * �e���p�^�[��6
     */
	void ShotPattern6();

	/**
	 * �q�b�g�|�C���g�l�擾
	 */
	int GetHitPoint() const { return _hitpoint; }

	/**
	 * �V�[���h�l�擾
	 */
	int GetShield() const { return _shield; }

	/**
	 * �t�F�[�Y���擾
	 */
	int GetPhase() const { return _phase; }

	static Boss* GetInstance() { return _pInstance; }

	static Boss* _pInstance;

	// �v���C���[�N���X�Ŏg�p
	int _bulletNum;      // �_�E�����O�ɏo�����Ă����e�̐��J�E���g
	bool _mlsDownFlag;   // MLS�Œe���Ԃ��ꂽ�e�Ń_�E������Ɓutrue�v

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

	int  _gameClearCnt;  // �N���A�J�E���g
	bool _gameClearFlag; // �N���A�t���O

	static constexpr float SHOT_DISTANCE = 10.0f;  // �e���𔭐�������ʒu(�{�X���S����̋���)
	static constexpr float ADD_POS_Y     = 8.5f;  // �����蔻��pY���W���Z�l

	static constexpr int PATTERN_CHANGE_CNT = 240; // �e���p�^�[����ω�������J�E���g�ő�l
	static constexpr int SHOT_REVERSE_CNT = 90;    // �e����]������ω�������J�E���g�ő�l
	static constexpr int PHASE_ONE_HP   = 4000;    // �t�F�[�Y1�ֈڍs����c��HP��
	static constexpr int PHASE_TWO_HP   = 3000;    // �t�F�[�Y2�ֈڍs����c��HP��
	static constexpr int PHASE_THREE_HP = 2000;    // �t�F�[�Y3�ֈڍs����c��HP��
	static constexpr int PHASE_FOUR_HP  = 1000;    // �t�F�[�Y4�ֈڍs����c��HP��
	static constexpr int MIN_DOWN_TIME = 180;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)
	static constexpr int DOWN_TIME_ONE_BULLET = 90;      // �_�E�����ԍŏ��l(�_�E�����Ԍv�Z�p)

};

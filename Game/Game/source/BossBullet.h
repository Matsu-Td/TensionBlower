#pragma once

/**
 * @file  BossBullet.h
 * @brief �{�X�̒e������
 *
 * @date 2021-02-08
 */

#include "appframe.h"

class BossBullet : public ObjectBase{
public:
	BossBullet();
	virtual ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();
	void Shot();

	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }
	void SetShotSpd(float shotSpd) { _shotSpd = shotSpd; }

private:
	int _cg[2];
	float _shotSpd;         // �e�̈ړ����x
	int _shotCnt;           // 
	int _mlsCnt;
	int _pattern;           // �e���p�^�[���ؑ�(3�p�^�[��)
	float _shotAngle;       // �e�������p�x
	float _setAngle;        // �e�������p�x�ݒ�
	float shotInterval;     // �e�������C���^�[�o��
	bool _camStateMLS;      // �J�������:�}���`���b�N�I���V�X�e����������
	bool _canLockFlag;      // MLS�Ń��b�N�\�����ƂȂ�
	bool _repelFlag;        // �e���ꂽ��(true:�e���ꂽ, false:�e����ĂȂ�)
	float _bulletDir;       // -1.0f��MLS�ɂ��e�̂͂����Ԃ�

	static constexpr float NOR_SPD = 1.0f;
};
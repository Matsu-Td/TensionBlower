/**
 * @file   BossBomb.h
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "appframe.h"

class BossBomb : public ObjectBase {
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();

	VECTOR _vTarg;
	float _shotSpd;         // �e�̈ړ����x
	float _upSpd;
	int _shotCnt;           // 
	int _mlsCnt;
	float _shotAngle;       // �e�������p�x
	float _setAngle;        // �e�������p�x�ݒ�
	float shotInterval;     // �e�������C���^�[�o��
	bool _camStateMLS;      // �J�������:�}���`���b�N�I���V�X�e����������
	bool _canLockFlag;      // MLS�Ń��b�N�\�����ƂȂ�
	bool _repelFlag;        // �e���ꂽ��(true:�e���ꂽ, false:�e����ĂȂ�)
	float _bulletDir;       // -1.0f��MLS�ɂ��e�̂͂����Ԃ�

	enum STATE {
		UP,
		STOP,
		ATTACK,
	};
	STATE _state;
};

/**
 * @file   BossBullet.h
 * @brief  �{�X�̒e������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"

class BossBullet : public ObjectBase{
public:
	BossBullet(VECTOR pos, float shotSpd, float shotAngle);
    ~BossBullet();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BULLET; }

	void Initialize();
	void Process();
	void Render();

	/**
	 * �e�̈ړ�����
	 */
	void MoveShot();

	/**
	 * @brief �e���Ԃ�����
	 */
	void Repel();

	/**
	 * @brief �e�̊p�x��ݒ�
	 * @param shotAngle �e�̊p�x
	 */
	void SetAngle(float shotAngle) { _shotAngle = shotAngle; }

	/**
	 * @brief �e�̑��x��ݒ�
	 * @param shotSpd �e�̑��x
	 */
	void SetShotSpd(float shotSpd) { _shotSpd = shotSpd; }

	/**
	 * @brief �����蔻��
	 */
	void Collision();

private:
	int   _cg[2];
	float _shotSpd;         // �e�̈ړ����x
	float _shotAngle;       // �e�������p�x
	bool  _camStateMLS;     // �J�������:�}���`���b�N�I���V�X�e����������
	bool  _canLockFlag;     // MLS�Ń��b�N�\�����ƂȂ�
	bool  _repelFlag;       // �e���ꂽ��(true:�e���ꂽ, false:�e����ĂȂ�)
	float _bulletDir;       // -1.0f��MLS�ɂ��e�̂͂����Ԃ�

	static constexpr float REPEL_SPD = 3.0f; // �e���Ԃ��ꂽ��̒e�̈ړ����x
	static constexpr float MLS_SPD = 0.01f;  // �}���`���b�N�I���V�X�e�����̑��x�v�Z(�ʏ��1/100��)
};
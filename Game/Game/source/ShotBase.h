/**
 * @file   ShotBase.h
 * @brief  �e�������N���X�̊��N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/22
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"
#include "BossDamage.h"
#include <list>

class ShotBase : public ObjectBase{
public:
	/**
	 * @brief ������
	 */
	virtual void Initialize();

	/**
	 * @brief �t���[�������F�v�Z
	 */
	virtual void Process();

	/**
	 * @brief �t���[�������F�`��
	 */
	virtual void Render();

	/**
	 * @brief �e�̈ړ�����
	 */
	virtual void Move();

	/**
	 * @brief �����蔻��
	 */
	virtual void Collision();


protected:
	int _cg[2];            // �摜
	VECTOR _vTarg;         // �W�I�̈ʒu
	float _shotAngle;      // �e�������p�x
	float _shotSpd;        // �e�̈ړ����x
	float _upSpd;          // �㏸�J�E���g
	int _shotCnt;          // �V���b�g�J�E���g
	int _mlsCnt;           // �}���`���b�N�I���V�X�e�����̃J�E���g
	bool _camStateMLS;     // �J�������:�}���`���b�N�I���V�X�e����������
	bool _canLockFlag;     // MLS�Ń��b�N�\�����ƂȂ�
	bool _repelFlag;       // �e���ꂽ��(true:�e���ꂽ, false:�e����ĂȂ�)

	enum class STATE {
		NORMAL,   // �ʏ�
		UP,       // �㏸
		STOP,     // ��~
		SNIPER,   // �_��
		REPEL,    // �e���Ԃ��ꂽ���
	};
	STATE _state; // ���

	static constexpr float REPEL_SPD = 3.0f; // �e���Ԃ��ꂽ��̒e�̈ړ����x
	static constexpr float MLS_SPD = 0.01f; // �}���`���b�N�I���V�X�e�����̑��x�v�Z(�ʏ��1/100��)

private:
	std::unique_ptr<BossDamage> _bossDamageCall;  	// �{�X�ւ̃_���[�W�����Ăяo��
};
/**
 * @file   BossBomb.h
 * @brief  �{�X�̃{���U������
 * 
 * @author matsuo tadahiko
 * @date   2021/03/03
 */

#pragma once

#include "appframe.h"
#include "ObjectBase.h"

class BossBomb : public ObjectBase {
public:
	/**
	 * @brief �{������
	 * @param pos �{���̔����ʒu
	 */
	BossBomb(VECTOR pos);
	~BossBomb();

	virtual OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::BOSS_BOMB; }

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

private:
	int _cg[2];            // �摜
	VECTOR _vTarg;         // �W�I�̈ʒu(�v���C���[�̈ʒu)
	float _shotSpd;        // �e�̈ړ����x
	float _upSpd;          // �㏸�J�E���g
	int _shotCnt;          // �V���b�g�J�E���g
	int _mlsCnt;           // �}���`���b�N�I���V�X�e�����̃J�E���g
	bool _camStateMLS;     // �J�������:�}���`���b�N�I���V�X�e����������
	bool _canLockFlag;     // MLS�Ń��b�N�\�����ƂȂ�
	bool _repelFlag;       // �e���ꂽ��(true:�e���ꂽ, false:�e����ĂȂ�)
	
	enum class STATE {
		UP,       // �㏸
		STOP,     // ��~
		SNIPER,   // �_��
		REPEL,
	};
	STATE _state;

	static constexpr int UP_CNT = 24;    // �㏸�J�E���g
	static constexpr int STOP_CNT = 24;  // ��~�J�E���g
	static constexpr float MLS_SPD = 0.01f; // �}���`���b�N�I���V�X�e�����̑��x�v�Z(�ʏ��1/100��)
};

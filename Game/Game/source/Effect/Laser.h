/**
 * @file   Laser.h
 * @brief  �{�X�̃��[�U�[�U��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

class Laser : public ObjectBase{
public:
	/**
	 * ���[�U�[����
	 * @param pos     ���[�U�[���ˈʒu
	 * @param radius  �{�X����̔��a
	 * @param angle   ���[�U�[�̔��ˊp�x�A�ʒu
	 * @param roteSpd ���[�U�[�̉�]���x
	 */
	Laser(VECTOR pos,float radius, float angle, float roteSpd);
	~Laser();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::LASER; }

	/**
	 * ������
	 */
	void Initialize() override;

	/**
	 * �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * �t���[���v�Z�F�`��
	 */
	void Render() override;

private:
	int	  _effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	  _playingHandle;	// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	float _roteAngle; // ��]�p�x
	float _roteSpd;   // ��]���x
	float _radius;    // �{�X����̔��a
	int _effectCnt;   // �G�t�F�N�g�Đ��J�E���g
	int _mlsCnt;      // �}���`���b�N�I���V�X�e���������̃J�E���g

	const float MLS_SPD = 0.01f; // �}���`���b�N�I���V�X�e�����̑��x�v�Z(�ʏ��1/100��)
};
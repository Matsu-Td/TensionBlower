/**
 * @file   Laser.h
 * @brief  �{�X�̃��[�U�[�U���N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/02/14
 */

#pragma once

#include "appframe.h"
#include "../Object/ObjectBase.h"

/**
 * @brief �{�X�̃��[�U�[�U���N���X
 */
class Laser : public ObjectBase{
public:
	/**
	 * @brief ���[�U�[����
	 * @param pos     ���[�U�[���ˈʒu
	 * @param radius  �{�X����̔��a
	 * @param angle   ���[�U�[�̔��ˊp�x�A�ʒu
	 * @param roteSpd ���[�U�[�̉�]���x
	 */
	Laser(VECTOR pos,float radius, float angle, float roteSpd);
	~Laser();

	OBJECTTYPE GetType() { return ObjectBase::OBJECTTYPE::LASER; }

	/**
	 * @brief ������
	 */
	void Initialize() override;

	/**
	 * @brief �t���[�������F�v�Z
	 */
	void Process() override;

	/**
	 * @brief �t���[���v�Z�F�`��
	 */
	void Render() override;

private:
	/**
	 * @brief ���[�U�[���폜����
	 */
	void Deletion();

	int	  _effectHandle;  // �G�t�F�N�g�t�@�C�������[�h����n���h��
	int	  _playingHandle; // ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	int   _effectCnt; // �G�t�F�N�g�Đ��J�E���g
	int   _mlsCnt;    // �}���`���b�N�I���V�X�e���������̃J�E���g
	float _roteAngle; // ��]�p�x
	float _roteSpd;   // ��]���x
	float _radius;    // �{�X����̔��a

	const float MLS_SPD      = 0.01f;  // �}���`���b�N�I���V�X�e�����̑��x�v�Z(�ʏ��1/100��)
	const float LASER_LENGTH = 125.0f; // ���[�U�[�̑S��
};
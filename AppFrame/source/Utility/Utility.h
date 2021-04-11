/** 
 * @file   Utility.h
 * @brief  �L�p�֐�
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Dxlib.h"

namespace Util {
	/**
	 * @brief ���X�e�B�b�N X,Y���p�����[�^�擾
	 * @param paramX X���p�����[�^
	 * @param paramY Y���p�����[�^
	 */
	void GetLeftStickParamXY(float& paramX, float& paramY);

	/**
	 * @brief ���X�e�B�b�N �ړ��ʎ擾
	 * @return ���X�e�B�b�N�̈ړ���
	 */
	float GetLeftStickLength();

	/**
	 * @brief ���X�e�B�b�N��|�����p�x(radian)�擾
	 * @return ���X�e�B�b�N�p�x(radian)
	 */
	float GetLeftStickRad();

	/**
	 * @brief ���X�e�B�b�N��|�����p�x(degree)
	 * @return ���X�e�B�b�N�p�x(degree)
	 */
	float GetLeftStickDeg();
}

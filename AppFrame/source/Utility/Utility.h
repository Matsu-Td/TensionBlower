/** 
 * @file   Utility.h
 * @brief  �L�p�֐��A�ϐ�
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Dxlib.h"

namespace util {

	/**
	 * @brief ���X�e�B�b�N X,Y���p�����[�^�擾
	 * @param paramX X���p�����[�^
	 * @param paramY Y���p�����[�^
	 */
	void GetLeftStickParamXY(float& paramX, float& paramY);

	/**
	 * @brief  ���X�e�B�b�N �ړ��ʎ擾
	 * @return ���X�e�B�b�N�̈ړ���
	 */
	float GetLeftStickLength();

	/**
	 * @brief  ���X�e�B�b�N��|�����p�x(radian)�擾
	 * @return ���X�e�B�b�N�p�x(radian)
	 */
	float GetLeftStickRad();

	/**
	 * @brief  ���X�e�B�b�N��|�����p�x(degree)
	 * @return ���X�e�B�b�N�p�x(degree)
	 */
	float GetLeftStickDeg();

	/**
	 * @brief  �������v�Z
	 * @return �v�Z����
	 */
	template<typename T>
	T Sqrt(T x, T y);

	/**
	 * @brief �x��(deg)�����W�A��(rad)�ɕϊ�
	 */
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * DX_PI_F); }

	/**
	 * @brief ���W�A��(rad)��x��(deg)�ɕϊ�
	 */
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / DX_PI_F); }

	// ���X�e�B�b�N�̍ŏ��l(�������Ȃ��͈�)
	constexpr float ANALOG_MIN = 0.3f;
}
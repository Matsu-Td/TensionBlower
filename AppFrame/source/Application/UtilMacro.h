#pragma once

#define	SAFE_DELETE(x)	if(x){delete x;x=nullptr;}

namespace Util {
	/*
	 * �v�Z�p
	 */
	constexpr float PI = 3.1415926535897932386f;

	//  �x��(deg)�����W�A��(rad)�ɕϊ�
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * PI); }

	// ���W�A��(rad)��x��(deg)�ɕϊ�
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / PI); }

	// ���X�e�B�b�N�̍ŏ��l(�������Ȃ��͈�)
	constexpr float ANALOG_MIN = 0.3f;
}
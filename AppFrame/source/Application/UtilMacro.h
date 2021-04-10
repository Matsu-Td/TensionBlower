#pragma once

#define	SAFE_DELETE(x)	if(x){delete x;x=nullptr;}

namespace Util {
	/*
	 * �v�Z�p
	 */
	constexpr float PI = 3.1415926535897932386f;

	//  �x�������W�A���ɕϊ�
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * PI); }

	// ���W�A����x���ɕϊ�
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / PI); }
}
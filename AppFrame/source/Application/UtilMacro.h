#pragma once

#define	SAFE_DELETE(x)	if(x){delete x;x=nullptr;}

namespace Util {
	/*
	 * 計算用
	 */
	constexpr float PI = 3.1415926535897932386f;

	//  度数をラジアンに変換
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * PI); }

	// ラジアンを度数に変換
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / PI); }
}
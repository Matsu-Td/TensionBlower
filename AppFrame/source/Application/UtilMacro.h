#pragma once

#define	SAFE_DELETE(x)	if(x){delete x;x=nullptr;}

namespace Util {
	/*
	 * 計算用
	 */
	constexpr float PI = 3.1415926535897932386f;

	//  度数(deg)をラジアン(rad)に変換
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * PI); }

	// ラジアン(rad)を度数(deg)に変換
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / PI); }

	// 左スティックの最小値(反応しない範囲)
	constexpr float ANALOG_MIN = 0.3f;
}
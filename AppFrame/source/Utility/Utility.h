/** 
 * @file   Utility.h
 * @brief  有用関数、変数
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Dxlib.h"

namespace util {

	/**
	 * @brief 左スティック X,Y軸パラメータ取得
	 * @param paramX X軸パラメータ
	 * @param paramY Y軸パラメータ
	 */
	void GetLeftStickParamXY(float& paramX, float& paramY);

	/**
	 * @brief  左スティック 移動量取得
	 * @return 左スティックの移動量
	 */
	float GetLeftStickLength();

	/**
	 * @brief  左スティックを倒した角度(radian)取得
	 * @return 左スティック角度(radian)
	 */
	float GetLeftStickRad();

	/**
	 * @brief  左スティックを倒した角度(degree)
	 * @return 左スティック角度(degree)
	 */
	float GetLeftStickDeg();

	/**
	 * @brief  平方根計算
	 * @return 計算結果
	 */
	template<typename T>
	T Sqrt(T x, T y);

	/**
	 * @brief 度数(deg)をラジアン(rad)に変換
	 */
	template<typename T>
	float DegToRad(T deg) { return ((deg) / 180.0f * DX_PI_F); }

	/**
	 * @brief ラジアン(rad)を度数(deg)に変換
	 */
	template<typename T>
	float RadToDeg(T rad) { return ((rad) * 180.0f / DX_PI_F); }

	// 左スティックの最小値(反応しない範囲)
	constexpr float ANALOG_MIN = 0.3f;
}
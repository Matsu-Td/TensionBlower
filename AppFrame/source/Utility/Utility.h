/** 
 * @file   Utility.h
 * @brief  有用関数
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Dxlib.h"

namespace Util {
	/**
	 * @brief 左スティック X,Y軸パラメータ取得
	 * @param paramX X軸パラメータ
	 * @param paramY Y軸パラメータ
	 */
	void GetLeftStickParamXY(float& paramX, float& paramY);

	/**
	 * @brief 左スティック 移動量取得
	 * @return 左スティックの移動量
	 */
	float GetLeftStickLength();

	/**
	 * @brief 左スティックを倒した角度(radian)取得
	 * @return 左スティック角度(radian)
	 */
	float GetLeftStickRad();

	/**
	 * @brief 左スティックを倒した角度(degree)
	 * @return 左スティック角度(degree)
	 */
	float GetLeftStickDeg();
}

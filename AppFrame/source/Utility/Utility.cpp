/** 
 * @file   Utility.cpp
 * @brief  —L—pŠÖ”’è‹`
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Utility.h"
#include "../Application/ApplicationBase.h"
#include <iostream>

namespace Util {

	void GetLeftStickParamXY(float& paramX, float& paramY) {

		DINPUT_JOYSTATE dInput = appframe::ApplicationBase::GetInstance()->GetDInputState();

		paramX = static_cast<float>(dInput.X);
		paramY = static_cast<float>(dInput.Y);
	}

	float GetLeftStickLength() {

		DINPUT_JOYSTATE dInput = appframe::ApplicationBase::GetInstance()->GetDInputState();

		float paramX, paramY;
		GetLeftStickParamXY(paramX, paramY);

		float length = Sqrt(paramX, paramY);

		return length;
	}

	float GetLeftStickRad() {

		DINPUT_JOYSTATE dInput = appframe::ApplicationBase::GetInstance()->GetDInputState();

		float paramX, paramY;
		GetLeftStickParamXY(paramX, paramY);

		float rad = atan2(paramX, paramY);

		return rad;
	}

	float GetLeftStickDeg() {

		float rad = GetLeftStickRad();
		float deg = Util::RadToDeg(rad);

		return deg;
	}

	template<typename T>
	T Sqrt(T x, T y) {
		return static_cast<T>(sqrt(std::pow(x, 2.0) + std::pow(y, 2.0)));
	}
}

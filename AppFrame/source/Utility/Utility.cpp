/** 
 * @file   Utility.cpp
 * @brief  —L—pŠÖ”’è‹`
 * 
 * @author matsuo tadahiko
 * @date   2021/04/11
 */

#include "Utility.h"
#include "../Application/UtilMacro.h"
#include "../Application/ApplicationBase.h"
#include <iostream>

namespace Util {

	void GetLeftStickParamXY(float& paramX, float& paramY) {

		DINPUT_JOYSTATE dInput = ApplicationBase::GetInstance()->GetDInputState();

		paramX = static_cast<float>(dInput.X);
		paramY = static_cast<float>(dInput.Y);
	}

	float GetLeftStickLength() {

		DINPUT_JOYSTATE dInput = ApplicationBase::GetInstance()->GetDInputState();

		float paramX, paramY;
		GetLeftStickParamXY(paramX, paramY);

		float length = sqrt(std::pow(paramX, 2.0) + std::pow(paramY, 2.0));

		return length;
	}

	float GetLeftStickRad() {

		DINPUT_JOYSTATE dInput = ApplicationBase::GetInstance()->GetDInputState();

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
}

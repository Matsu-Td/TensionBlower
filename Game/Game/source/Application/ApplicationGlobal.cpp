/**
 * @file   ApplicationGlobal.cpp
 * @brief  �O���[�o���ϐ���`
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appFrame.h"
#include "ApplicationGlobal.h"

// ����
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() 
{
}

ApplicationGlobal::~ApplicationGlobal() 
{
}

/**
 * ������
 */
bool ApplicationGlobal::Initialize() {

	_gameEndFlag = false;

	return true;
}

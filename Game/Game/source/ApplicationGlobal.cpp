/**
 * @file   ApplicationGlobal.cpp
 * @brief  �O���[�o���ϐ���`
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "AppFrame.h"
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
bool ApplicationGlobal::Init() {

	_gameEndFlag = false;

	return true;
}

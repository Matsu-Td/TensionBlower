
/**
 * @file  ApplicationGlobal.cpp
 * @brief �O���[�o���ϐ���`
 *
 * @date 2021-02-08
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

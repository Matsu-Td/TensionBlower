
/**
 * @file  ApplicationGlobal.cpp
 * @brief グローバル変数定義
 *
 * @date 2021-02-08
 */

#include "AppFrame.h"
#include "ApplicationGlobal.h"

// 実体
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() 
{
}

ApplicationGlobal::~ApplicationGlobal() 
{
}


bool ApplicationGlobal::Init() {

	_gameEndFlag = false;

	return true;
}

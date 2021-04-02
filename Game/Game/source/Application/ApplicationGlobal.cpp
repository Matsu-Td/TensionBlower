/**
 * @file   ApplicationGlobal.cpp
 * @brief  グローバル変数定義
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "appFrame.h"
#include "ApplicationGlobal.h"

// 実体
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() 
{
}

ApplicationGlobal::~ApplicationGlobal() 
{
}

/**
 * 初期化
 */
bool ApplicationGlobal::Initialize() {

	_gameEndFlag = false;

	return true;
}

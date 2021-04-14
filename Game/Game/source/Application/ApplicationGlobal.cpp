/**
 * @file   ApplicationGlobal.cpp
 * @brief  グローバル変数定義
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#include "appFrame.h"
#include "ApplicationGlobal.h"

using namespace tensionblower;

// 実体
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() {
	// 何もしない
}

ApplicationGlobal::~ApplicationGlobal() {
	// 何もしない
}

/*
 * 初期化
 */
bool ApplicationGlobal::Initialize() {

	_gameEndFlag = false;

	return true;
}
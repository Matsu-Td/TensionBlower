/**
 * @file   ApplicationGlobal.cpp
 * @brief  �O���[�o���ϐ���`
 * 
 * @author matsuo tadahiko
 * @date   2021/01/20
 */

#include "appFrame.h"
#include "ApplicationGlobal.h"

using namespace tensionblower;

// ����
ApplicationGlobal	gGlobal;

ApplicationGlobal::ApplicationGlobal() {
	// �������Ȃ�
}

ApplicationGlobal::~ApplicationGlobal() {
	// �������Ȃ�
}

/*
 * ������
 */
bool ApplicationGlobal::Initialize() {

	_gameEndFlag = false;

	return true;
}
/**
 * @file  ApplicationBase.cpp
 * @brief �A�v���P�[�V�������N���X
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "ApplicationBase.h"

using namespace appframe;

ApplicationBase	*ApplicationBase::_pInstance = nullptr;


ApplicationBase::ApplicationBase() :_key(0), _keyTrg(0), _dInput({0}) {
	_pInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

/*
 * ������
 */
bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		// �E�B���h�E���[�h(TRUE)���t���X�N���[�����[�h(FALSE)���w��
		ChangeWindowMode(FALSE);		
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (DxLib_Init() == -1){	
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// Effekseer������
	if (Effekseer_Init(8000) == -1){
		DxLib_End();
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = std::make_unique<mode::ModeServer>();
	
	return true;
}

/*
 * ���
 */
bool ApplicationBase::Terminate() {
	// Effekseer���I��
	Effkseer_End();
	// DX���C�u�����J��
	DxLib_End();

	return true;
}

/*
 * �t���[�������F����
 */
bool ApplicationBase::Input() {

	int keyold = _key;
	
	_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_keyTrg = (_key ^ keyold) & _key;	// �L�[�̃g���K��񐶐�
	GetJoypadDirectInputState(DX_INPUT_PAD1, &_dInput);

	return true;
}

/*
 * �t���[�������F�v�Z
 */
bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();

	return true;
}

/*
 * �t���[�������F�`��
 */
bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();

	return true;
}

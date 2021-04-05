/**
 * @file  ApplicationBase.cpp
 * @brief �A�v���P�[�V�������N���X
 *
 * @author matsuo tadahiko
 * @date   2020/12/18
 */

#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_pInstance = nullptr;


ApplicationBase::ApplicationBase() {
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

	// Effekseer������������
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��
	if (Effekseer_Init(100000) == -1){
		DxLib_End();
		return -1;
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ�
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// ����������
	srand((unsigned int)time(NULL));

	// ���[�h�T�[�o�̏�����
	_serverMode = std::make_unique<ModeServer>();
	
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

	int keyold = _gKey;
	_gKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gTrg = (_gKey ^ keyold) & _gKey;	// �L�[�̃g���K��񐶐�

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

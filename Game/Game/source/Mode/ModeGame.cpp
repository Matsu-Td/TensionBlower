/**
 * @file   ModeGame.cpp
 * @brief  �Q�[�����[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "../Sound/Sound.h"

/**
 * ���C�g�̃f�B�t���[�Y�J���[��ݒ肷��
 */
void ModeGame::SetLightColorHandle(int lightHandle) {
	SetLightDifColorHandle(lightHandle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(lightHandle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(lightHandle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));
}

/**
 * ������
 */
bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	PlaySoundMem(gSound._bgm["boss"], DX_PLAYTYPE_LOOP);

	// JSON�t�@�C������L�����f�[�^�ǂݍ���
	_charaData = std::make_unique<CharaData>("res/json/", "CharaData");

	// �I�u�W�F�N�g�T�[�o�[�ɓo�^
	_objServer.Add(NEW Stage()); 
	_objServer.Add(NEW Player()); 
	_objServer.Add(NEW Boss());
	
	// �O���[�o���ϐ�������(���U���g��ʁA�X�R�A�v�Z�p)
	gGlobal._remainingHP = 0;
	gGlobal._totalRepelCnt = 0;
	gGlobal._totalGetEnergy = 0;

	// �Q�[���X�^�[�g�\��
	ModeServer::GetInstance()->Add(NEW ModeGameStart, 2, "start");
	_objServer.Process();
	_stopObjProcess = true;

	// ���C�g�̐ݒ�
	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.164f, 0.164f, 0.164f, 0.0f));

	int Light0Handle = CreateDirLightHandle(VGet(0.062f, -0.479f, 0.875f));
	SetLightColorHandle(Light0Handle);

	int Light1Handle = CreateDirLightHandle(VGet(-0.878f, 0.479f, 0.000f));
	SetLightColorHandle(Light1Handle);

	int Light2Handle = CreateDirLightHandle(VGet(0.878f, 0.479f, 0.000f));
    SetLightColorHandle(Light2Handle);

	int Light3Handle = CreateDirLightHandle(VGet(0.062f, 0.479f, -0.875f));
    SetLightColorHandle(Light3Handle);

	return true;
}

/**
 * ���
 */
bool ModeGame::Terminate() {
	base::Terminate();

	// ���C�g�n���h���폜
	DeleteLightHandleAll();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGame::Process() {
	base::Process();

	// �L�[�̃g���K���擾
	int trg = ApplicationMain::GetInstance()->GetTrg();
	
	// �I�u�W�F�N�g�̏�����~�v��
	if (_stopObjProcess == false) {
		_objServer.Process();
	}
	_cam.Process();

    // Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// �Q�[���p�b�h�uSTART�v�{�^���Ń|�[�Y���[�h�ǉ�
	if (trg & PAD_INPUT_8) { 
		ModePause* modePause = NEW ModePause();
		ModeServer::GetInstance()->Add(modePause, 99, "pause");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeGame::Render() {
	base::Render();
	
	// 3D�`��ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);	

	// �I�u�W�F�N�g�̕`��
	_objServer.Render();

	// �J�������̕`��
	_cam.Render();

	// �C���Q�[����UI�`��
	_playerStatus.Render();
	_bossStatus.Render();

	// �G�t�F�N�V�A�f�[�^�̍Đ��A�`��
	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}


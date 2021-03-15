/**
 * @file   ModeGame.cpp
 * @brief  �Q�[���{��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "Sound.h"
#include <memory>

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

	SetLightEnable(FALSE);
	SetGlobalAmbientLight(GetColorF(0.164f, 0.164f, 0.164f, 0.0f));

	int Light0Handle = CreateDirLightHandle(VGet(0.062f, -0.479f, 0.875f));
	SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light0Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light1Handle = CreateDirLightHandle(VGet(-0.878f, 0.479f, 0.000f));
	SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light2Handle = CreateDirLightHandle(VGet(0.878f, 0.479f, 0.000f));
	SetLightDifColorHandle(Light2Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light2Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light2Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	int Light3Handle = CreateDirLightHandle(VGet(0.062f, 0.479f, -0.875f));
	SetLightDifColorHandle(Light3Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	SetLightSpcColorHandle(Light3Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	SetLightAmbColorHandle(Light3Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//// ���C�g�̐ݒ�
	//SetLightEnable(FALSE);
	//SetGlobalAmbientLight(GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	//int Light0Handle = CreatePointLightHandle(VGet(-125.000f, 100.000f, 0.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light0Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light0Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light0Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light1Handle = CreatePointLightHandle(VGet(125.000f, 100.000f, 0.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light1Handle, GetColorF(1.000f, 1.000f, 1.000f, 0.000f));
	//SetLightSpcColorHandle(Light1Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light1Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light2Handle = CreatePointLightHandle(VGet(0.000f, 100.000f, -125.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light2Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light2Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light2Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

	//int Light3Handle = CreatePointLightHandle(VGet(0.000f, 100.000f, 125.000f), 2000.000f, 2.500f, 0.000f, 0.000f);
	//SetLightDifColorHandle(Light3Handle, GetColorF(1.000f, 1.000f, 1.000f, 1.000f));
	//SetLightSpcColorHandle(Light3Handle, GetColorF(0.500f, 0.500f, 0.500f, 0.000f));
	//SetLightAmbColorHandle(Light3Handle, GetColorF(0.000f, 0.000f, 0.000f, 0.000f));

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

	int trg = ApplicationMain::GetInstance()->GetTrg();

	
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
	
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);	
	
	_objServer.Render();

	_cam.Render();
	_playerStatus.Render();
	_bossStatus.Render();

	Effekseer_Sync3DSetting();
	DrawEffekseer3D();

	return true;
}


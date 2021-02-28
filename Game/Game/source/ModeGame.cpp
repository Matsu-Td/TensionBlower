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

	PlaySoundMem(gSound._bgm["boss"], DX_PLAYTYPE_BACK);

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

	return true;
}

/**
 * ���
 */
bool ModeGame::Terminate() {
	base::Terminate();

	// �I�u�W�F�N�g�T�[�o�[�̃R���e�i�ɓo�^���Ă����v�f��S�č폜�A���������
	_objServer.Clear();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGame::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	_cam.Process();
	_objServer.Process();

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


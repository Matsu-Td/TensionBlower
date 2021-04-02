/**
 * @file   ModeGameStart.cpp
 * @brief  MISSION START�����\��
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"
#include "../Player/PlayerVoice.h"

/**
 * ������
 */
bool ModeGameStart::Initialize() {
	if (!base::Initialize()) { return false; }

	// �N���A���̐��f�[�^�Đ�
	PlaySoundMem(gPlayerVoice._vc["gamestart"], DX_PLAYTYPE_BACK);

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/missionstart.png");

	return true;
}

/**
 * ���
 */
bool ModeGameStart::Terminate() {
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGameStart::Process() {
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (trg & PAD_INPUT_2) {
		ModeGame* modeGame = static_cast<ModeGame*>(ModeServer::GetInstance()->Get("game"));
		modeGame->_stopObjProcess = false;
		// �uMISSION START�v �\���������Ă���N���A�^�C���J�E���g�X�^�[�g
		gGlobal._gameTime = GetNowCount();
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeGameStart::Render() {
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}

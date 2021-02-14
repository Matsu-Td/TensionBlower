
/**
 * @file  ModeGameStart.cpp
 * @brief MISSION START�����\��
 *
 * @date 2021-02-14
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameStart.h"

/**
 * ������
 */
bool ModeGameStart::Initialize() {
	if (!base::Initialize()) { return false; }

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

	DrawGraph(0, POS_Y, _cg[0], TRUE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}

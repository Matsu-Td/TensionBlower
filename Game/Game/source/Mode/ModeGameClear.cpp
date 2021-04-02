/**
 * @file   ModeGameClear.cpp
 * @brief  �Q�[���N���A���[�h�N���X
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "../Application/ApplicationMain.h"
#include "../Application/ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeResult.h"
#include "../Sound/Sound.h"
#include "../Player/PlayerVoice.h"

/**
 * ������
 */
bool ModeGameClear::Initialize(){
	if (!base::Initialize()) { return false; }

	// �{�X�X�e�[�W��BGM�Đ���~
	StopSoundMem(gSound._bgm["boss"]);
	// �N���A���Đ�
	PlaySoundMem(gSound._se["win"], DX_PLAYTYPE_BACK);
	// �N���A���̐��f�[�^�Đ�
	PlaySoundMem(gPlayerVoice._vc["clear"], DX_PLAYTYPE_BACK);

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/missionclear.png");

	// �N���A����܂ł̌o�ߎ��Ԃ��i�[
	gGlobal._gameTime = GetNowCount() - gGlobal._gameTime;

	return true;
}

/**
 * ���
 */
bool ModeGameClear::Terminate(){
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGameClear::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// �Q�[���p�b�h�uB�v�{�^���ŃQ�[���N���A���[�h�ƃQ�[�����[�h���폜���A
	// ���U���g���[�h�ǉ�
	if (trg & PAD_INPUT_2) {  
		StopSoundMem(gSound._se["win"]);
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeServer::GetInstance()->Add(NEW ModeResult(), 1, "result");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeGameClear::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}
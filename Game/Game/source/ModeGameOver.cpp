/**
 * @file   ModeGameOver.cpp
 * @brief  �Q�[���I�[�o�[���
 * 
 * @author matsuo tadahiko
 * @date   2021/03/01
 */

#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeGameOver.h"
#include "ModeTitle.h"
#include "Sound.h"

/**
 * ������
 */
bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	// �{�X�X�e�[�W��BGM�Đ���~
	StopSoundMem(gSound._bgm["boss"]);

	_cg[0] = ResourceServer::LoadGraph("res/band.png");
	_cg[1] = ResourceServer::LoadGraph("res/gameover.png");

	return true;
}

/**
 * ���
 */
bool ModeGameOver::Terminate(){
	base::Terminate();

	return true;
}

/**
 * �t���[�������F�v�Z
 */
bool ModeGameOver::Process(){
	base::Process();

	int trg = ApplicationMain::GetInstance()->GetTrg();

	ModeServer::GetInstance()->SkipProcessUnderLayer();

	// �Q�[���p�b�h�uB�v�{�^���ŃQ�[���I�[�o�[���[�h�ƃQ�[�����[�h���폜���A
	// �^�C�g�����[�h��ǉ�
	if (trg & PAD_INPUT_2) {
		ModeServer::GetInstance()->Del(this);
		ModeServer::GetInstance()->Del(ModeServer::GetInstance()->Get("game"));

		ModeServer::GetInstance()->Add(NEW ModeTitle, 1, "title");
	}

	return true;
}

/**
 * �t���[�������F�`��
 */
bool ModeGameOver::Render(){
	base::Render();

	DrawGraph(0, POS_Y, _cg[0], FALSE);
	DrawGraph(0, POS_Y, _cg[1], TRUE);

	return true;
}